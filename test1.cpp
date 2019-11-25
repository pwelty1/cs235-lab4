#include <iostream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <locale>
#include <map>

#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"


using namespace std;

int main (){
  Relation rel1;
  Relation rel2;
  Relation rel3;
  Relation rel4;

  vector<string> attbs{"cat", "dog", "fish"};
  vector<string> attbs1{"cat", "fish", "bird", "bunny"};
  vector<string> attbs5{"cat", "dog", "fish"};
  vector<string> attbs9{"shark", "eagle", "buffalo"};
  rel1.addRelation("beta",attbs);
  rel2.addRelation("alpha", attbs1);
  rel3.addRelation("phi", attbs5);
  rel4.addRelation("omega", attbs9);

  rel1.insert({"1","2","5"});
  rel1.insert({"1","4","1"});
  rel1.insert({"2","3","2"});
  rel1.insert({"3","3","2"});
  rel1.insert({"6","7","4"});

  rel2.insert({"3","4","2","4"});
  rel2.insert({"6","4","9","2"});
  rel2.insert({"4","3","2","7"});
  rel2.insert({"1","5","2","4"});
  rel2.insert({"1","5","8","3"});

  rel3.insert({"1","2","5"});
  rel3.insert({"1","4","1"});
  rel3.insert({"2","3","2"});
  rel3.insert({"3","3","2"});
  rel3.insert({"6","7","4"});

  rel4.insert({"1","2","5"});
  rel4.insert({"1","4","1"});
  rel4.insert({"2","3","2"});
  rel4.insert({"3","3","2"});
  rel4.insert({"6","7","4"});

  Relation output1 = rel1;
  Relation output2 = rel1;
  Relation output3 = rel1;


  cout << "***************" << endl;
    map<string, int> Rel2indicies;
    Scheme attbs2= rel2.getAttbs();
    for(unsigned int j = 0; j< attbs2.size(); ++j){
      Rel2indicies.insert(pair<string, int>(attbs2.at(j),j));
    }
    map<string, int>  Resultindicies;
    Scheme attbs3= rel1.getAttbs();
    for(unsigned int j = 0; j< attbs3.size(); ++j){
      Resultindicies.insert(pair<string, int>(attbs3.at(j),j));
    }
    output1.combineSchemes(attbs2);
    output1.combineTuples(output1.getTuples(), rel2.getTuples(), Resultindicies, Rel2indicies);

    map<string, int> wanted;
    Scheme attbs4 = output1.getAttbs();
    for (unsigned int i = 0; i < attbs4.size(); ++i) {
      wanted.insert(pair<string, int>(attbs4.at(i),i));
    }
    output1.project(wanted);
    output1.rename(wanted);

    output1.toString();
  cout << "***************" << endl;

  cout << "***************" << endl;
    map<string, int> Rel3indicies;
    Scheme attbs6= rel3.getAttbs();
    for(unsigned int j = 0; j< attbs6.size(); ++j){
      Rel3indicies.insert(pair<string, int>(attbs6.at(j),j));
    }
    map<string, int>  Result1indicies;
    Scheme attbs7= rel1.getAttbs();
    for(unsigned int j = 0; j< attbs7.size(); ++j){
      Result1indicies.insert(pair<string, int>(attbs7.at(j),j));
    }
    output2.combineSchemes(attbs6);
    output2.combineTuples(output2.getTuples(), rel3.getTuples(), Result1indicies, Rel3indicies);
    map<string, int> wanted1;
    Scheme attbs8 = output2.getAttbs();
    for (unsigned int i = 0; i < attbs8.size(); ++i) {
      wanted1.insert(pair<string, int>(attbs8.at(i),i));
    }
    output2.project(wanted1);
    output2.rename(wanted1);

    output2.toString();
  cout << "***************" << endl;

  cout << "***************" << endl;
    map<string, int> Rel4indicies;
    Scheme attbs10= rel4.getAttbs();
    for(unsigned int j = 0; j< attbs10.size(); ++j){
      Rel4indicies.insert(pair<string, int>(attbs10.at(j),j));
    }
    map<string, int>  Result2indicies;
    Scheme attbs11= rel1.getAttbs();
    for(unsigned int j = 0; j < attbs11.size(); ++j){
      Result2indicies.insert(pair<string, int>(attbs11.at(j),j));
    }
    output3.combineSchemes(attbs10);
    output3.combineTuples(output3.getTuples(), rel4.getTuples(), Result2indicies, Rel4indicies);
    map<string, int> wanted2;
    Scheme attbs12 = output3.getAttbs();
    for (unsigned int i = 0; i < attbs12.size(); ++i) {
      wanted2.insert(pair<string, int>(attbs12.at(i),i));
    }
    output3.project(wanted2);
    output3.rename(wanted2);

    output3.toString();
  cout << "***************" << endl;

  return 0;
}
