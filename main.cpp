#include "interpreter/nodes/concrete_nodes.h"
#include "interpreter/visitors/print_visitor.h"
#include "interpreter/visitors/eval_visitor.h"
#include "interpreter/lexer/lexer.h"
#include "interpreter/parser/parser.h"
#include <fstream>

int main(int argc, char** argv){

    //TODO: add future argument checks.
    if (argc < 2){
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        return -1;
    }



    std::string fileName = argv[1];
    std::ifstream file(fileName);
    
    if (!file.is_open()){
         std::cerr << "Error: invalid file " << fileName << std::endl;
         return -1;
    }

    std::string input = "";

    while (!file.eof()){
        input += file.get(); //get every character in file
    }
    //display file content (debugging)
    std::cout << input << std::endl;

    //lexer converts string into tokens
    Lexer lexer;
    std::vector<Token> tokens = lexer.lex(input);

    //diplay tokens (debugging)
    for (int i=0; i<tokens.size(); i++){
        std::cout << "Token(" << tokens[i].type << ", " << tokens[i].text << ", " << tokens[i].startPos << ')'<< std::endl;
    }

    //parse tokens into AST 
    Parser parser(tokens);
    std::unique_ptr<ProgramNode> node = parser.parse();

    //print out AST
    PrintVisitor printVisitor;
    node->accept(printVisitor);
    

    return 0;
}