#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(const Quad* quadList, int quadSize, const Symbol* symbolTable, int symbolSize)
        : quads(quadList), qSize(quadSize), symbols(symbolTable), sSize(symbolSize) {}

void CodeGenerator::processSymbolTable(){
    Symbol sym;
    for (int i = 0; i < sSize; i++) {
        sym = symbols[i];
        if (sym.type == "PROGRAM_NAME") {
            programName = sym.token;
        }
        if (sym.type == "CONSTVAR" || sym.type == "NUMERIC_LITERAL") {
            dataSymbols[dataSize++] = sym;
        }
        if (sym.type == "IDENTIFIER" || sym.type == "INTVAR") {
            bssSymbols[bssSize++] = sym;
        }
    }
}

void CodeGenerator::genLinuxDefs() {
    asmCode << "; Definitions for Linux\n";
    asmCode << "sys_exit\tequ\t1\n" << "sys_read\tequ\t3\n" << "sys_write\tequ\t3\n";
    asmCode << "stdin\t\tequ\t0\n" << "stdout\t\tequ\t1\n" << "stderr\t\tequ\t3\n\n";
}

void CodeGenerator::genDataSection(){
    asmCode << "section .data\n";
    asmCode << "\tuserMsg\tdb\t'Enter an integer(less than 32,765): '\n";
    asmCode << "\tlenUserMsg\tequ\t$ - userMsg\n";
    asmCode << "\tdisplayMsg\tdb\t'You entered: '\n";
    asmCode << "\tlenDisplayMsg\tequ\t$ - displayMsg\n\n";
    asmCode << "\tnewline\tdb\t0xA\n";
    asmCode << "\tTen\tdb\t10\n\n";
    asmCode << "\tResult\t\tdb\t'Ans = '\n";
    asmCode << "\tResultValue\tdb\t'aaaaa'\n";
    asmCode << "\t\t\t\tdb\t0xA\n"; 
    asmCode << "\tResultEnd\tequ\t$ - Results\n\n";
    asmCode << "\tnum\t\ttimes 6 db 'ABCDEF'\n";
    asmCode << "\tnumEnd\tequ\t$ - num\n\n";
    for (int i = 0; i < dataSize; i++) {
        if (dataSymbols[i].type == "NUMERIC_LITERAL"){
            asmCode << "\tLit" << dataSymbols[i].token << "\tDW\t" << dataSymbols[i].value << "\n";
        } else {
        asmCode << "\t" << dataSymbols[i].token << "\t\tDW\t" << dataSymbols[i].value << "\n";
        }
    }
    asmCode << "\n";
}

void CodeGenerator::genBssSection() {
    asmCode << "section .bss\n";
    asmCode << "\tTempChar\tRESB\t1\n";
    asmCode << "\ttestchar\tRESB\t1\n";
    asmCode << "\tReadInt\t\tRESW\t1\n";
    asmCode << "\ttempint\t\tRESW\t1\n";
    asmCode << "\tnegflag\t\tRESB\t1\n\n";
    for(int i = 0; i < bssSize; i++) {
        asmCode << "\t" << bssSymbols[i].token << "\t\tRESW\t1\n";
    }
    asmCode << "\n\n";
}

void CodeGenerator::genTextSection() {
    asmCode << "; Start of program\n";
    asmCode << "\tglobal _start\n";
    asmCode << "section .text\n\n";
    asmCode << "_start: nop\n";
    asmCode << "\n";
    // Process quads and create assembly language
    asmCode << "; =========Process Quads Put Assembly Here=========\n\n";
    asmCode << "; exit code\n";
    asmCode << "fini:\n";
    asmCode << "\t mov eax, sys_exit\n";
    asmCode << "\t xor ebx, ebx\n";
    asmCode << "\tint 80h\n";
    asmCode << "; End " << programName << ".asm\n\n\n";
    
}

void CodeGenerator::genPrintString() {
    asmCode << "; PrintString\tPROC\n";
    asmCode << "PrintString:\n";
    asmCode << "\tpush ax\n";
    asmCode << "\tpush dx\n";
    asmCode << "\tmov eax, 4\n";
    asmCode << "\tmov ebx, 1\n";
    asmCode << "\tmov ecx, userMsg\n";
    asmCode << "\tmov edx, lenUserMsg\n";
    asmCode << "\tint 80h\n";
    asmCode << "\tpop dx\n";
    asmCode << "\tpop ax\n";
    asmCode << "\tret\n";
    asmCode << "; PrintString\tENDP\n\n\n";
}

void CodeGenerator::genGetInterger() {
    asmCode << "; GetAnInteger/tPROC\n";
    asmCode << "GetAnInteger:\n";
    asmCode << "\tmov eax, 3\n";
    asmCode << "\tmov ebx, 2\n";
    asmCode << "\tmov ecx, num\n";
    asmCode << "\tint 0x80\n";
    asmCode << "\tmov edx, eax\n";
    asmCode << "\tmov eax, 4\n";
    asmCode << "\tmov ebx, 1\n";
    asmCode << "\tmov ecx, num\n";
    asmCode << "\tint 80h\n";
    asmCode << "; GetAnInteger\tENDP\n\n\n";
}

void CodeGenerator::genConvertStringToInt() {

}

void CodeGenerator::genConvertIntToString() {

}

void CodeGenerator::writeAsmFile() {
    string filename = programName + ".asm";
    ofstream asmFile(filename);
    if(!asmFile.is_open()) {
        throw runtime_error("Couldn't open file: " + filename);
    }
    asmFile << asmCode.str();
    asmFile.close();
}

void CodeGenerator::generateAssembly() {
    processSymbolTable();
    genLinuxDefs();
    genDataSection();
    genBssSection();
    genTextSection();
    genPrintString();
    genGetInterger();
    writeAsmFile();
}