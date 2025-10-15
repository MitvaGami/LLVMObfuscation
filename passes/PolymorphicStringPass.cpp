#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Constants.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include <random>
#include <vector>
#include <string>

using namespace llvm;

struct PolymorphicStringPass : public PassInfoMixin<PolymorphicStringPass> {
private:
    std::mt19937 rng;
    int encrypted_count = 0;
    
    // Multiple encryption algorithms
    enum EncryptionType {
        XOR_CIPHER,
        CAESAR_CIPHER,
        SUBSTITUTION_CIPHER,
        MULTI_LAYER_XOR
    };
    
    std::vector<uint8_t> encryptXOR(const std::string& str, uint8_t key) {
        std::vector<uint8_t> encrypted;
        for (char c : str) {
            encrypted.push_back(c ^ key);
        }
        encrypted.push_back(0); // null terminator
        return encrypted;
    }
    
    std::vector<uint8_t> encryptCaesar(const std::string& str, int shift) {
        std::vector<uint8_t> encrypted;
        for (char c : str) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                encrypted.push_back((c - base + shift) % 26 + base);
            } else {
                encrypted.push_back(c);
            }
        }
        encrypted.push_back(0);
        return encrypted;
    }
    
    std::vector<uint8_t> encryptMultiXOR(const std::string& str) {
        std::vector<uint8_t> encrypted;
        std::vector<uint8_t> keys = {0x5A, 0x3C, 0x71, 0x91};
        
        for (size_t i = 0; i < str.length(); i++) {
            uint8_t key = keys[i % keys.size()];
            encrypted.push_back(str[i] ^ key ^ (i & 0xFF));
        }
        encrypted.push_back(0);
        return encrypted;
    }
    
    Function* createDecryptFunction(Module& M, EncryptionType type, const std::vector<uint8_t>& params) {
        LLVMContext& ctx = M.getContext();
        
        std::string funcName = "decrypt_" + std::to_string(rng() % 10000);
        FunctionType* funcType = FunctionType::get(
            Type::getInt8Ty(ctx)->getPointerTo(), // CORRECTED
            {Type::getInt8Ty(ctx)->getPointerTo()}, // CORRECTED
            false
        );
        
        Function* decryptFunc = Function::Create(funcType, Function::InternalLinkage, funcName, &M);
        BasicBlock* entry = BasicBlock::Create(ctx, "entry", decryptFunc);
        IRBuilder<> builder(entry);
        
        Argument* encStr = decryptFunc->getArg(0);
        
        // Allocate buffer for decrypted string
        Value* len = ConstantInt::get(Type::getInt32Ty(ctx), 256); // Max length
        AllocaInst* buffer = builder.CreateAlloca(Type::getInt8Ty(ctx), len, "decrypt_buffer");
        
        // Create decryption loop based on type
        switch (type) {
            case XOR_CIPHER: {
                uint8_t key = params[0];
                BasicBlock* loopBB = BasicBlock::Create(ctx, "loop", decryptFunc);
                BasicBlock* exitBB = BasicBlock::Create(ctx, "exit", decryptFunc);
                
                // Initialize counter
                AllocaInst* counter = builder.CreateAlloca(Type::getInt32Ty(ctx), nullptr, "counter");
                builder.CreateStore(ConstantInt::get(Type::getInt32Ty(ctx), 0), counter);
                builder.CreateBr(loopBB);
                
                // Loop body
                builder.SetInsertPoint(loopBB);
                Value* i = builder.CreateLoad(Type::getInt32Ty(ctx), counter);
                Value* srcPtr = builder.CreateGEP(Type::getInt8Ty(ctx), encStr, i);
                Value* dstPtr = builder.CreateGEP(Type::getInt8Ty(ctx), buffer, i);
                
                Value* encByte = builder.CreateLoad(Type::getInt8Ty(ctx), srcPtr);
                Value* keyVal = ConstantInt::get(Type::getInt8Ty(ctx), key);
                Value* decByte = builder.CreateXor(encByte, keyVal);
                builder.CreateStore(decByte, dstPtr);
                
                // Check for null terminator
                Value* isNull = builder.CreateICmpEQ(encByte, ConstantInt::get(Type::getInt8Ty(ctx), key));
                Value* nextI = builder.CreateAdd(i, ConstantInt::get(Type::getInt32Ty(ctx), 1));
                builder.CreateStore(nextI, counter);
                builder.CreateCondBr(isNull, exitBB, loopBB);
                
                builder.SetInsertPoint(exitBB);
                break;
            }
            default:
                // Fallback to simple XOR
                break;
        }
        
        builder.CreateRet(buffer);
        return decryptFunc;
    }
    
public:
    PolymorphicStringPass() : rng(std::random_device{}()) {}
    
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        encrypted_count = 0;
        LLVMContext& ctx = M.getContext();
        
        // Find all string constants
        std::vector<GlobalVariable*> stringGlobals;
        for (GlobalVariable& GV : M.globals()) {
            if (GV.hasInitializer() && isa<ConstantDataArray>(GV.getInitializer())) {
                if (ConstantDataArray* CDA = dyn_cast<ConstantDataArray>(GV.getInitializer())) {
                    if (CDA->isString()) {
                        stringGlobals.push_back(&GV);
                    }
                }
            }
        }
        
        // Encrypt each string with random algorithm
        for (GlobalVariable* GV : stringGlobals) {
            ConstantDataArray* CDA = cast<ConstantDataArray>(GV->getInitializer());
            std::string originalStr = CDA->getAsString().str();
            
            if (originalStr.length() < 2) continue; // Skip very short strings
            
            // Choose random encryption
            EncryptionType encType = static_cast<EncryptionType>(rng() % 4);
            std::vector<uint8_t> encrypted;
            std::vector<uint8_t> params;
            
            switch (encType) {
                case XOR_CIPHER: {
                    uint8_t key = rng() % 256;
                    params.push_back(key);
                    encrypted = encryptXOR(originalStr, key);
                    break;
                }
                case MULTI_LAYER_XOR:
                    encrypted = encryptMultiXOR(originalStr);
                    break;
                default:
                    uint8_t key = rng() % 256;
                    params.push_back(key);
                    encrypted = encryptXOR(originalStr, key);
            }
            
            // Create new encrypted global
            ArrayType* arrayType = ArrayType::get(Type::getInt8Ty(ctx), encrypted.size());
            std::vector<Constant*> encryptedConstants;
            for (uint8_t byte : encrypted) {
                encryptedConstants.push_back(ConstantInt::get(Type::getInt8Ty(ctx), byte));
            }
            
            Constant* encryptedArray = ConstantArray::get(arrayType, encryptedConstants);
            GlobalVariable* encGV = new GlobalVariable(
                M, arrayType, true, GlobalValue::PrivateLinkage, 
                encryptedArray, "enc_str_" + std::to_string(encrypted_count)
            );
            
            // Create decrypt function
            Function* decryptFunc = createDecryptFunction(M, encType, params);
            
            // Replace all uses with decrypt function calls
            std::vector<User*> users(GV->users().begin(), GV->users().end());
            for (User* user : users) {
                if (Instruction* inst = dyn_cast<Instruction>(user)) {
                    IRBuilder<> builder(inst);
                    
                    // Cast encrypted global to i8*
                    Value* encPtr = builder.CreateBitCast(encGV, Type::getInt8Ty(ctx)->getPointerTo()); // CORRECTED
                    
                    // Call decrypt function
                    Value* decrypted = builder.CreateCall(decryptFunc, {encPtr});
                    
                    // Replace the use
                    inst->replaceUsesOfWith(GV, decrypted);
                }
            }
            
            encrypted_count++;
        }
        
        errs() << "PolymorphicStringPass: Encrypted " << encrypted_count << " strings\n";
        return PreservedAnalyses::none();
    }
};

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "PolymorphicStringPass", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "poly-string") {
                            MPM.addPass(PolymorphicStringPass());
                            return true;
                        }
                        return false;
                    });
            }};
}
