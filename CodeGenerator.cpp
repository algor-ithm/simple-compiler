#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(const Quad* quadList, int quadSize, const Symbol* symbolTable, int symbolSize)
        : quads(quadList), qSize(quadSize), symbols(symbolTable), sSize(symbolSize) {}

void CodeGenerator::processSymbolTable(){
    Symbol sym;
    bool found;
    for (int i = 0; i < sSize; i++) {
        sym = symbols[i];
        if (sym.type == "PROGRAM_NAME") {
            programName = sym.token;
        }
        if (sym.type == "CONSTVAR") {
            dataSymbols[dataSize++] = sym;
        }
        if (sym.type == "NUMERIC_LITERAL") {
            found = false;
            for (int j =  0; j < dataSize; j++) {
                if (dataSymbols[j].token == sym.token){
                    found = true;
                }
            }
            if (!found) {
                dataSymbols[dataSize++] = sym;
            }
        }
        if (sym.type == "IDENTIFIER" || sym.type == "INTVAR") {
            bssSymbols[bssSize++] = sym;
        }
    }
}

void CodeGenerator::processQuads(){
    Quad quad; 
    for (int i = 0; i < qSize; i++) {
        quad = quads[i];
        if (quad.op == "+") {
            asmCode << "\tmov ax, [" << quad.leftArg << "]\n";
            asmCode << "\tadd ax, [" << quad.rightArg << "]\n";
            asmCode << "\tmov [" << quad.result << "], ax\n\n";
        }
        if (quad.op == "-"){
            asmCode << "\tmov ax, [" << quad.leftArg << "]\n";
            asmCode << "\tsub ax, [" << quad.rightArg << "]\n";
            asmCode << "\tmov [" << quad.result << "], ax\n\n";
        }
        if (quad.op == "*") {
            asmCode << "\tmov ax, [" << quad.leftArg << "]\n";
            asmCode << "\tmul word [" << quad.rightArg << "]\n";
            asmCode << "\tmov [" << quad.result << "], ax\n\n";
        }
        if (quad.op == "/") {
            asmCode << "\tmov dx, 0\n";
            asmCode << "\tmov ax, [" << quad.leftArg << "]\n";
            asmCode << "\tmov cx, [" << quad.rightArg << "]\n";
            asmCode << "\tdiv cx\n";
            asmCode << "\tmov [" << quad.result  << "], ax\n\n";

        }
        if (quad.op == "=") {
            asmCode << "\tmov ax, [" << quad.rightArg << "]\n";
            asmCode << "\tmov [" << quad.leftArg << "], ax\n\n";
        }
        if (quad.op == ">" || quad.op == ">=" || quad.op == "<" 
            || quad.op == "<=" || quad.op == "==" || quad.op == "!=") {
            asmCode << "\tmov ax, [" << quad.leftArg << "]\n";
            asmCode << "\tcmp ax, [" << quad.rightArg << "]\n";
        }
        if (quad.op == "GET") {
            asmCode << "\tcall\tPrintString\n";
            asmCode << "\tcall\tGetAnInteger\n";
            asmCode << "\tmov ax, [ReadInt]\n";
            asmCode << "\tmov [" << quad.leftArg << "], ax";
            asmCode << "\t\t\t; Read " << quad.leftArg << "\n\n";
        }
        if (quad.op == "PUT") {
            asmCode << "\tmov ax, [" << quad.leftArg << "]";
            asmCode << "\t\t ; Write " << quad.leftArg << "\n";
            asmCode << "\tcall ConvertIntegerToString\n";
            asmCode << "\tmov eax, 4\n";
            asmCode << "\tmov ebx, 1\n";
            asmCode << "\tmov ecx, Result\n";
            asmCode << "\tmov edx, ResultEnd\n";
            asmCode << "\tint 80h\n\n";
        }
        if (quad.op == "THEN") {
            asmCode << "\tJ" << quad.rightArg << " " << quad.leftArg << "\n\n";  
        }
        if (quad.op == "WHILE") {
            asmCode << quad.leftArg << ":\n";
        }
        if (quad.op == "DO") {
            asmCode << "\tJ" << quad.rightArg << " " << quad.leftArg << "\n\n";
        }
        if (quad.leftArg == "JLABEL") {
            asmCode << quad.op << ":\tnop\n";
        }
        if (quad.leftArg == "WLABEL") {
            asmCode << "\tjmp" << " " << quad.op << "\n\n"; 
        }
    }
}

void CodeGenerator::genLinuxDefs() {
    asmCode << "; Definitions for Linux\n";
    asmCode << "sys_exit\tequ\t1\n" << "sys_read\tequ\t3\n" << "sys_write\tequ\t4\n";
    asmCode << "stdin\t\tequ\t0\n" << "stdout\t\tequ\t1\n" << "stderr\t\tequ\t3\n\n";
}

void CodeGenerator::genDataSection(){
    asmCode << "section .data\n";
    asmCode << "\tuserMsg\t\t\tdb\t'Enter an integer(less than 32,765): '\n";
    asmCode << "\tlenUserMsg\t\tequ\t$ - userMsg\n";
    asmCode << "\tdisplayMsg\t\tdb\t'You entered: '\n";
    asmCode << "\tlenDisplayMsg\tequ\t$ - displayMsg\n\n";
    asmCode << "\tnewline\tdb\t0xA\n";
    asmCode << "\tTen\t\tDW\t10\n\n";
    asmCode << "\tResult\t\tdb\t'Ans = '\n";
    asmCode << "\tResultValue\tdb\t'aaaaa'\n";
    asmCode << "\t\t\t\tdb\t0xA\n"; 
    asmCode << "\tResultEnd\tequ\t$ - Result\n\n";
    asmCode << "\tnum\t\ttimes 6 db 'ABCDEF'\n";
    asmCode << "\tnumEnd\tequ\t$ - num\n\n";
    for (int i = 0; i < dataSize; i++) {
        if (dataSymbols[i].type == "NUMERIC_LITERAL"){
            asmCode << "\t" << dataSymbols[i].token << "\tDW\t" << dataSymbols[i].value << "\n";
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
    processQuads();
    // done with assembly
    asmCode << "\n; exit code\n";
    asmCode << "fini:\n";
    asmCode << "\tmov eax, sys_exit\n";
    asmCode << "\txor ebx, ebx\n";
    asmCode << "\tint 80h\n\n";
    asmCode << "; End " << programName << ".asm\n\n\n";
}

void CodeGenerator::genPrintString() {
    asmCode << "; PrintString\tPROC\n";
    asmCode << "PrintString:\n";
    asmCode << "\tpush\tax\n";
    asmCode << "\tpush\tdx\n";
    asmCode << "\tmov eax, 4\n";
    asmCode << "\tmov ebx, 1\n";
    asmCode << "\tmov ecx, userMsg\n";
    asmCode << "\tmov edx, lenUserMsg\n";
    asmCode << "\tint 80h\n";
    asmCode << "\tpop\t\tdx\n";
    asmCode << "\tpop\t\tax\n";
    asmCode << "\tret\n";
    asmCode << "; PrintString\tENDP\n\n\n";
}

void CodeGenerator::genGetInterger() {
    asmCode << "; GetAnInteger\tPROC\n";
    asmCode << "GetAnInteger:\n";
    asmCode << "\tmov eax, 3\n";
    asmCode << "\tmov ebx, 2\n";
    asmCode << "\tmov ecx, num\n";
    asmCode << "\tmov edx, 6\n";
    asmCode << "\tint 0x80\n\n";
    asmCode << "\tmov edx, eax\n";
    asmCode << "\tmov eax, 4\n";
    asmCode << "\tmov ebx, 1\n";
    asmCode << "\tmov ecx, num\n";
    asmCode << "\tint 80h\n\n";
    // ConvertStringToInteger
    asmCode << "; ConvertStringToInteger PROC\n";
    asmCode << "ConvertStringToInteger:\n";
    asmCode << "\tmov ax, 0\n";
    asmCode << "\tmov [ReadInt], ax\n";
    asmCode << "\tmov ecx, num\n";
    asmCode << "\tmov bx, 0\n";
    asmCode << "\tmov bl, byte [ecx]\n\n";
    asmCode << "Next:\n\tsub bl, '0'\n";
    asmCode << "\tmov ax, [ReadInt]\n";
    asmCode << "\tmov dx, 10\n"; 
    asmCode << "\tmul dx\n";
    asmCode << "\tadd ax, bx\n";
    asmCode << "\tmov [ReadInt], ax\n\n";
    asmCode << "\tmov bx, 0\n";
    asmCode << "\tadd ecx, 1\n";
    asmCode << "\tmov bl, byte [ecx]\n\n";
    asmCode << "\tcmp bl, 0xA\n";
    asmCode << "\tjne Next\n";
    asmCode << "\tret\n";
    asmCode << "; ConvertStringToInteger ENDP\n";
    asmCode << "; GetAnInteger\tENDP\n\n";
}

void CodeGenerator::genConvertIntToString() {
    asmCode << "; ConvertIntegerToString\tPROC\n\n";
    asmCode << "ConvertIntegerToString:\n";
    asmCode << "\tmov ebx, ResultValue + 4\n\n";
    asmCode << "ConvertLoop:\n";
    asmCode << "\tsub dx, dx\n";
    asmCode << "\tmov cx, 10\n";
    asmCode << "\tdiv cx\n";
    asmCode << "\tadd dl, '0'\n";
    asmCode << "\tmov [ebx], dl\n";
    asmCode << "\tdec ebx\n";
    asmCode << "\tcmp ebx, ResultValue\n";
    asmCode << "\tjge ConvertLoop\n";
    asmCode << "\tret\n";
    asmCode << "; ConvertIntegerToString\tENDP";
}

void CodeGenerator::writeAsmFile() {
    string filename = "assemblyFiles/" + programName + ".asm";
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
    genConvertIntToString();
    writeAsmFile();
}