#include<iostream>
#include<string>
#include<vector>
#include<regex>
using namespace std;

struct Token{
    string type;
    string value;
};

vector<Token> tokenize(const string &code)
{
    vector<Token>tokens;
    regex pattern(R"(int|if|==|[a-zA-Z_]\w*|\d+|[+\-=;{}()])");
    smatch match;
    string::const_iterator searchStart(code.cbegin());
    
    while(regex_search(searchStart,code.cend(),match,pattern)){
        string value=match[0];
        if(value=="int" || value=="if")
            tokens.push_back({"KEYWORD",value});
        else if(regex_match(value,regex("\\d+")))
            tokens.push_back({"LITERAL",value});
        else if(regex_match(value,regex("[a-zA-Z_]\\w*")))
            tokens.push_back({"IDENTIFIER",value});
        else if(regex_match(value,regex("[+\\-=]"))|| value=="==")
            tokens.push_back({"OPERATOR",value});
        else
            tokens.push_back({"PUNCTUATION",value});
        searchStart=match.suffix().first;
    }
    return tokens;
}

void printTokens(const vector<Token>&tokens){
    for(const auto &token:tokens){
        cout<<"["<<token.type<<" "<<token.value<<"]";
        cout<<endl;
    }
}

struct ASTNode
{
    string type;
    string value;
    vector<ASTNode*>children;
    ASTNode(string t,string v):type(t),value(v){}
};

ASTNode* parse(const vector<Token> &tokens) {
    ASTNode *root=new ASTNode("Program","");
    for (size_t i=0;i<tokens.size();++i)
    {
         // Declaration
        if(tokens[i].value=="int")
        {
            root->children.push_back(new ASTNode("Declaration" ,tokens[i + 1].value));
            i+=2;
        }
        // Assignment
        else if(tokens[i].type=="IDENTIFIER" && tokens[i+1].value=="=")
        { 
            auto assign=new ASTNode("Assignment",tokens[i].value);
            assign->children.push_back(new ASTNode("Value", tokens[i+2].value));
            root->children.push_back(assign);
            i+=3;
        }
        //Conditional
        else if(tokens[i].value=="if"){
            auto conditional=new ASTNode("Conditional","");
            conditional->children.push_back(new ASTNode("Condition",tokens[i+2].value+" "+tokens[i+3].value+" "+tokens[i+4].value));
            root->children.push_back(conditional);
            i+=5;
        }
    }
    return root;
}

void printAST(ASTNode *node, int depth = 0) {
    for(int i=0;i<depth;++i) {
    cout<< "  ";
    cout<<node->type<<":"<<node->value<<endl;
    }
    for(auto child:node->children) 
    printAST(child,depth+1);
}


void generateAssembly(ASTNode *node){
    if(node->type=="Program")
    {
        for(auto child:node->children)
        {
            generateAssembly(child);
        }
    }
    else if(node->type=="Declaration")
    {
        cout<<"DECLARE"<<node->value<<endl;
    }
    else if(node->type=="Assignment")
    {
        cout<<"LOAD"<<node->children[0]->value<<endl;
        cout<<"STORE"<<node->value<<endl;
    } else if(node->type=="Conditional"){
        cout<<"IF"<<node->children[0]->value<<"THEN"<<endl;
    }
}

int main() {
        string code = R"(
        int a;
        int b;
        a=10;
        if(a==10){b=a+1;}
    )"; //example to run
    auto tokens=tokenize(code);
    printTokens(tokens);

    auto ast=parse(tokens);
    printAST(ast);
    
    generateAssembly(ast);
    return 0;
}