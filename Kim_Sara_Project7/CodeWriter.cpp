//  CodeWriter.cpp
//  Project 7

#include "CodeWriter.h"
#include <string>
#include <fstream>
#include <iostream>

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

/************************************************************
 *                      void Close()
 * Closes the output file.
 *************************************************************/
void CodeWriter::Close(){
    outFile.close();
}
