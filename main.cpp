#include "interpreter/nodes/concrete_nodes.h"
#include "interpreter/visitors/print_visitor.h"
#include "interpreter/visitors/eval_visitor.h"
#include "interpreter/lexer/lexer.h"
#include "interpreter/parser/parser.h"
#include <fstream>
#include <unistd.h>

int main(int argc, char** argv){


    if (argc < 2){
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    bool shouldPrintDebug = false;

    int opt;
    while ((opt = getopt(argc, argv, "f:d")) != -1) {
        switch (opt) {
            case 'f':
                fileName = optarg;
                break;
            case 'd':
                shouldPrintDebug = true;
                break;
            default:
                std::cerr << "Error: Unkown argument "<< static_cast<char>(optopt) << std::endl;
                return 1;
        }
    }

    std::ifstream file(fileName);
    
    if (!file.is_open()){
         std::cerr << "Error: invalid file " << fileName << std::endl;
         return 1;
    }

    std::string input = "";

    while (!file.eof()){
        input += file.get(); //get every character in file
    }

    //lexer converts string into tokens
    Lexer lexer;
    std::vector<Token> tokens = lexer.lex(input);


    //parse tokens into AST 
    Parser parser(tokens);
    std::unique_ptr<ProgramNode> node = parser.parse();

    if (shouldPrintDebug){
        //display file content (debugging)
        std::cout << input << std::endl;

        //diplay tokens (debugging)
        for (int i=0; i<tokens.size(); i++){
            std::cout << "Token(" << tokens[i].type << ", " << tokens[i].text << ", " << tokens[i].startPos << ')'<< std::endl;
        }

        //print out AST
        PrintVisitor printVisitor;
        node->accept(printVisitor);
    }

    EvalVisitor evaluator;
    node->accept(evaluator);

    return 0;
}