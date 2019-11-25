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
  Relation rel5;

  vector<string> attbs{"cat", "dog", "fish"};
  vector<string> attbs1{"cat", "fish", "bird", "bunny"};
  vector<string> attbs5{"cat", "dog", "fish"};
  vector<string> attbs9{"cat", "dog", "fish"};
  vector<string> attbs10{"cat", "dog", "fish"};
  rel1.addRelation("beta",attbs);
  rel2.addRelation("alpha", attbs1);
  rel3.addRelation("phi", attbs5);
  rel4.addRelation("omega", attbs9);
  rel5.addRelation("pi", attbs10);

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

  rel4.insert({"1","2","3"});
  rel4.insert({"1","2","1"});
  rel4.insert({"2","2","2"});
  rel4.insert({"3","3","3"});
  rel4.insert({"8","7","4"});

  Relation output1 = rel1;
  Relation output2 = rel1;
  Relation output3 = rel5;


  cout << "***************" << endl;
  cout << "tuples added are:" << endl;
  output1.unite(rel3.getTuples());
  cout << "Resulting Relation:" << endl;
  output1.toString();
  cout << "***************" << endl;

  cout << "***************" << endl;
  cout << "tuples added are:" << endl;
  output2.unite(rel4.getTuples());
  cout << "Resulting Relation:" << endl;
  output2.toString();
  cout << "***************" << endl;

  cout << "***************" << endl;
  cout << "tuples added are:" << endl;
  output3.unite(rel4.getTuples());
  cout << "Resulting Relation:" << endl;
  output3.toString();
  cout << "***************" << endl;

  return 0;
}
