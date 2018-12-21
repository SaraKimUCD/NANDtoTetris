//  CodeWriter.cpp
//  Project 8

#include "CodeWriter.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


/************************************************************
 *                  CodeWriter(string filename)
 * Opens the output file/stream and gets ready to write into it.
 *************************************************************/
CodeWriter::CodeWriter(string filename){
    label = 0;
}

/************************************************************
 *                   ~CodeWriter()
 * Closes the output file/stream that was parsed
 *************************************************************/
CodeWriter::~CodeWriter(){
    label = 0;
    outFile.close();
}

/************************************************************
 *                      void setFileName
 * Informs the code writer that the translation of a new
 * VM file started.
 *************************************************************/
void CodeWriter::setFileName(string fileName) {
    outFile.open(fileName);
    writeInit();
}

/************************************************************
 *                      void writeArithmetic
 * Writes the assembly code that is the translation
 * of the given arithmetic command.
 *************************************************************/
void CodeWriter::writeArithmetic(string commandTest) {
    // Arithmetic List: add, sub, neg, eq, gt, lt, and, or, not
    
    // x OPERATION y
    if(commandTest == "add") {
        // get x's address so M->x
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        // Now D = x
        outFile << "D=M" << endl;
        
        // get y's address so M->y
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        // x + y
        outFile << "M=D+M" << endl;
        outFile << "@SP" << endl;
        outFile << "M=M+1" << endl;
    }
    
    else if(commandTest == "sub") {
        // get x's address so M->x
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        // Now D = x
        outFile << "D=M" << endl;
        
        // get y's address so M->y
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        // x - y
        outFile << "M=M-D" << endl;
        outFile << "@SP" << endl;
        outFile << "M=M+1" << endl;
    }
    
    else if(commandTest == "neg") {
        // get value
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        // negate value
        outFile << "M=-M" << endl;
    }
    
    else if(commandTest == "eq") {
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "D=M" << endl;
        
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "A=M" << endl;
        
        // Try subtracting 2 values to see whether it equals 0
        outFile << "D=M-D" << endl;
        outFile << "M=0" << endl;
        
        // if result eqauls 0, then that means both values are equal to each other
        outFile << "@"+to_string(label) << endl;
        outFile << "D;JEQ" << endl;
        outFile << "("+to_string(label)+")" << endl;
        
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        label = label + 1;
    }
    
    else if(commandTest == "gt") {
        // get the 2 different values to test
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "D=M"<< endl;
        
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "A=M" << endl;
        
        // Try subtracting 2 values to see whether it equals 0
        outFile << "D=D-M" << endl;
        outFile << "M=0" << endl;
        
        // if result is less than 0, then value1 < value2
        outFile << "D;JLT" << endl;
        outFile << "("+to_string(label)+")" << endl;
        
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        label = label + 1;
    }
    
    else if(commandTest == "lt") {
        // get the 2 different values to test
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "D=M"<< endl;
        
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "A=M" << endl;
        
        // Try subtracting 2 values to see whether it equals 0
        outFile << "D=D-M" << endl;
        outFile << "M=0" << endl;
        
        // if result is greater than 0, then value1 > value2
        outFile << "D;JGT" << endl;
        outFile << "("+to_string(label)+")" << endl;
        
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        label = label + 1;
    }
    
    else if(commandTest == "and") {
        // get first value so D = value1
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "D=M"<< endl;
        // get second value
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        // value1&value2
        outFile << "M=D&M" << endl;
    }
    
    else if(commandTest == "or") {
        // get first value so D = value1
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        outFile << "D=M"<< endl;
        // get second value
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        // value1&value2
        outFile << "M=D|M" << endl;
    }
    
    else if(commandTest == "not") {
        // get value
        outFile << "@SP" << endl;
        outFile << "M=M-1" << endl;
        // not value
        outFile << "M=!M" << endl;
    }
}

/************************************************************
 *                      void WritePushPop
 * Writes the assembly code that is the translation of
 * the given command, where command is C_PUSH/C_POP.
 *************************************************************/
void CodeWriter::WritePushPop(VM_Command commandTest, string segment, int index) {
    if(commandTest == C_PUSH){
        if(segment == "argument") {
            outFile << "@ARG" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "A=D+A" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        
        else if(segment == "constant") {
            outFile << "@"+to_string(index) << endl;
            outFile << "D=A" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        
        else if(segment == "local") {
            outFile << "@LCL" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "A=D+A" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        
        else if(segment == "this") {
            outFile << "@THIS" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "A=D+A" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        
        else if(segment == "that") {
            outFile << "@THAT" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "A=D+A" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        
        else if(segment == "pointer") {
            outFile << "@R3" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "A=D+A" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        
        else if(segment == "temp") {
            outFile << "@R5" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "A=D+A" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        
        else if(segment == "static") {
            outFile << "@static" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "A=D+A" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
    }
    
    else if(commandTest == C_POP){
        if(segment == "argument") {
            outFile << "@ARG" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        
        else if(segment == "constant") {
            outFile << "@constant" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        
        else if(segment == "local") {
            outFile << "@LCL" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        
        else if(segment == "this") {
            outFile << "@THIS" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        
        else if(segment == "that") {
            outFile << "@THAT" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        
        else if(segment == "pointer") {
            outFile << "@R3" << endl;
            outFile << "D=A" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        
        else if(segment == "temp") {
            outFile << "@R5" << endl;
            outFile << "D=A" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        
        else if(segment == "static") {
            outFile << "@static" << endl;
            outFile << "D=A" << endl;
            
            outFile << "@"+to_string(index) << endl;
            outFile << "D=D+A" << endl;
            
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            
            outFile << "@SP" << endl;
            outFile << "AM=M-1" << endl;
            outFile << "D=M" << endl;
            
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
    }
    
}
// Project 8
/************************************************************
*                        void writeInit
* Writes bootstrap code at start of the asm output file
*************************************************************/
void CodeWriter::writeInit(){
    // SP=256 -> Initialize the stack pointer to 0x0100
    // call Sys.init -> Start executing (the translated code of) Sys.init
    outFile << "@256" << endl;
    outFile << "D=A" << endl;
    outFile << "@SP" << endl;
    outFile << "M=D" << endl;
    writeCall("Sys.init", 0);
}

/************************************************************
 *                   void writeLabel
 * Writes the assembly code that is the translation of
 * the label command.
 *************************************************************/
void CodeWriter::writeLabel(string sLabel){
    outFile <<"("+sLabel+")"<< endl;
}

/************************************************************
 *                  void writeGoto
 * Writes the assembly code that is the translation of
 * the goto command.
 *************************************************************/
void CodeWriter::writeGoto(string sLabel){
    outFile << "@" << sLabel << endl;
    outFile << "0;JMP" << endl;
}

/************************************************************
 *                   void writeIf
 * Writes the assembly code that is the translation of
 * the if-goto command.
 *************************************************************/
void CodeWriter::writeIf(string sLabel){
    outFile << "@SP" << endl;
    outFile << "AM=M-1" << endl;
    outFile << "D=M" << endl;
    outFile << "@" << sLabel << endl;
    outFile << "D;JNE" << endl;
}

/************************************************************
 *                   void writeFunction
 * Writes the assembly code that is the translation of
 * the function command.
 *************************************************************/
void CodeWriter::writeFunction(string functionName, int numArgs){
    //cout << functionName << endl;;
    writeLabel(functionName);
    for(int i = 0; i < numArgs; i++) {
        WritePushPop(C_PUSH, "constant", 0);
    }
}

/************************************************************
 *                   void writeReturn
 * Writes the assembly code that is the translation of
 * the return command.
 *************************************************************/
void CodeWriter::writeReturn(){
    // frame = local
    outFile << "@LCL" << endl;
    outFile << "D=M" << endl;
    outFile << "@frame" << endl;
    outFile << "M=D" << endl;
    
    // RET = frame - 5
    outFile << "@5" << endl;
    outFile << "D=D-A" << endl;
    outFile << "A=D" << endl;
    outFile << "D=M" << endl;
    outFile << "@RET" << endl;
    outFile << "M=D" << endl;
    
    // SP = ARG + 1
    outFile << "@ARG" << endl;
    outFile << "D=M+1" << endl;
    outFile << "@SP" << endl;
    outFile << "M=D" << endl;
    
    // that = frame - 1
    outFile << "@frame" << endl;
    outFile << "D=M" << endl;
    outFile << "@1" << endl;
    outFile << "D=D-A" << endl;
    outFile << "A=D" << endl;
    outFile << "D=M" << endl;
    outFile << "@THAT" << endl;
    outFile << "M=D" << endl;
    
    // this = frame - 1
    outFile << "@frame" << endl;
    outFile << "D=M" << endl;
    outFile << "@2" << endl;
    outFile << "D=D-A" << endl;
    outFile << "A=D" << endl;
    outFile << "D=M" << endl;
    outFile << "@THIS" << endl;
    outFile << "M=D" << endl;
    
    // arg = frame - 1
    outFile << "@frame" << endl;
    outFile << "D=M" << endl;
    outFile << "@3" << endl;
    outFile << "D=D-A" << endl;
    outFile << "A=D" << endl;
    outFile << "D=M" << endl;
    outFile << "@ARG" << endl;
    outFile << "M=D" << endl;
    
    // lcl = frame - 1
    outFile << "@frame" << endl;
    outFile << "D=M" << endl;
    outFile << "@4" << endl;
    outFile << "D=D-A" << endl;
    outFile << "A=D" << endl;
    outFile << "D=M" << endl;
    outFile << "@LCL" << endl;
    outFile << "M=D" << endl;
    
    // go to ret
    outFile << "@RET" << endl;
    outFile << "A=M" << endl;
    outFile << "0;JMP" << endl;
}

/************************************************************
 *                   void writeCall
 * Writes the assembly code that is the translation of
 * the call command.
 *************************************************************/
void CodeWriter::writeCall(string functionName, int numArgs){
    // Push return address on stack
    // First convert label number to string to append with RETURN
    // to make return address name
    string labelStr;
    stringstream out;
    out << label;
    labelStr = out.str();
    string returnString = "RETURN" + string(labelStr);

    outFile << "@" << returnString << endl;
    outFile << "D=A" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    outFile << "@SP" << endl;
    outFile << "M=M+1" << endl;
    
    // Push local on stack
    outFile << "@LCL" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    outFile << "@SP" << endl;
    outFile << "M=M+1" << endl;
 
    // Push argument on stack
    outFile << "@ARG" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    outFile << "@SP" << endl;
    outFile << "M=M+1" << endl;
    
    // Push this on stack
    outFile << "@THIS" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    outFile << "@SP" << endl;
    outFile << "M=M+1" << endl;
    
    // Push that on stack
    outFile << "@THAT" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    outFile << "@SP" << endl;
    outFile << "M=M+1" << endl;
    
    // Position argument
    outFile << "@SP" << endl;
    outFile << "D=M" << endl;
    outFile << "@" << numArgs << endl;
    outFile << "D=D-A" << endl;
    outFile << "@5" << endl;
    outFile << "D=D-A" << endl;
    outFile << "@ARG" << endl;
    outFile << "M=D" << endl;
    
    // local = SP
    outFile << "@SP" << endl;
    outFile << "D=M" << endl;
    outFile << "@LCL" << endl;
    outFile << "M=D" << endl;
    
    writeGoto(functionName);
    writeLabel(returnString);
}

/************************************************************
 *                      void writeError
 * writes error to file if illegal command is found
 *************************************************************/
void CodeWriter::writeError(int lineNum){
    outFile << "ERROR! Line number " << lineNum << " has illegal command" << endl;
}

/************************************************************
 *                      void Close()
 * Closes the output file.
 *************************************************************/
void CodeWriter::Close(){
    outFile.close();
}

