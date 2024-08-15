#include "interpreter/nodes/concrete_nodes.h"
#include "interpreter/visitors/print_visitor.h"
#include "interpreter/visitors/eval_visitor.h"
#include "interpreter/lexer/lexer.h"
#include "interpreter/parser/parser.h"
#include <fstream>

int main(int argc, char** argv){

    if (argc >= 2){
        std::string fileName = argv[1];
        
        std::ifstream file(fileName);

        std::string input = "";
        
        if (file.is_open()){
            while (!file.eof()){
                input += file.get(); //get every character in file
            }
            std::cout << input << std::endl;
            Lexer lexer;
            std::vector<Token> tokens = lexer.lex(input);
            for (int i=0; i<tokens.size(); i++){
                std::cout << "Token(" << tokens[i].type << ", " << tokens[i].text << ", " << tokens[i].startPos << ')'<< std::endl;
            }

            Parser parser(tokens);
            std::unique_ptr<ProgramNode> node = parser.parse();
            PrintVisitor printVisitor;
            node->accept(printVisitor);
        }
        else{
            std::cerr << "Error: invalid file " << fileName << std::endl;
        }
    }
    else{
        std::cerr << "Error: Invalid number of arguments" << std::endl; 
    }

    return 0;
}