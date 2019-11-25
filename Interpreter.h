#ifndef INTERPRETER
#define INTERPRETER

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <exception>
#include <map>

#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Interpreter {
private:
  DatalogProgram oldData;
  vector<Rule> rulez;
  vector<Predicate> schemez;
  vector<Predicate> factz;
  vector<Predicate> queriez;
  Database db;

public:
   Interpreter(DatalogProgram data);
   void evalQuery(Predicate qury);
   void evaluateQueries();
   void evalRule(Rule rul);
   void evaluateRules();

};

Interpreter::Interpreter(DatalogProgram data) {
  oldData = data;
  rulez = data.getRules();
  schemez = data.getSchemes();
  factz = data.getFacts();
  queriez = data.getQueries();
  Relation rel;
  //Setting up all relations
  for (unsigned int i = 0; i < schemez.size(); ++i){
     rel.addRelation((schemez.at(i)).getId(), (schemez.at(i)).getParams());

     db.insert(pair<string,Relation>(rel.getName(), rel));
     rel.clearAttributes();
  }
  //filling relations
  for (unsigned int i= 0; i <factz.size(); ++i) {
    (db.find((factz.at(i)).getId())->second).insert((factz.at(i)).getParams());
  }


  //Printing out our database
  // map<string, Relation>::iterator it;
  //
  // for ( it = db.begin(); it != db.end(); it++ )
  // {
  //     cout << it->first << ':' << endl;
  //     (it->second).toString();
  //     cout << endl;
  // }
}

void Interpreter::evalQuery(Predicate qury) {
  map<string, int> variables1;
  vector<int> sameVars;
  map<string, vector<int>> variables;
  map<string,vector<int>> consts;
  vector<string> parameterz = qury.getParams();
  Relation newRel = db.find(qury.getId())->second;


  for (unsigned int i = 0; i < parameterz.size(); ++i){
    if (((parameterz.at(i)).front() == '\'') && ((parameterz.at(i)).back() == '\'')) {
      //cout << parameterz.at(i) << endl;
      newRel.selectConst(parameterz.at(i), i);
      if (consts.find(parameterz.at(i)) != consts.end()) {
        consts[parameterz.at(i)].push_back(i);
      }
      else {
        consts.insert(pair<string, vector<int>>(parameterz.at(i), sameVars));
        consts[parameterz.at(i)].push_back(i);
      }
      //newRel.toString();
      //cout << endl;
    }
    else {
        variables1.insert(pair<string, int>(parameterz.at(i),i));
        //cout << "done 5";
        if (variables.find(parameterz.at(i)) != variables.end()) {
          variables[parameterz.at(i)].push_back(i);
        }
        else {
          variables.insert(pair<string, vector<int> >(parameterz.at(i),sameVars));
          variables[parameterz.at(i)].push_back(i);
        }
      }
  }

  map<string, vector<int>>::iterator it1;
  for (it1 = variables.begin(); it1 != variables.end(); it1++ ){
      if ((it1->second).size() > 1) {
        for (unsigned int i  = 0; i < (it1->second).size(); ++i) {
          //cout << (it1->second).at(i) << endl;
          sameVars.push_back((it1->second).at(i));
        }
        newRel.selectVar(sameVars);
        sameVars.clear();
      }
  }

  newRel.project(variables1);
  newRel.rename(variables1);
  qury.toString();
  cout << "? ";
  if ((newRel.getTuples()).size() > 0){
    cout << "Yes(" << (newRel.getTuples()).size() << ")" << endl;
    if (variables1.size()> 0){
      newRel.toString();
    }
  }
  else{
    cout << "No" << endl;
  }
  //newRel.toString();
  //cout << endl;

  // map<string, vector<int>>::iterator it;
  //
  // for ( it = variables.begin(); it != variables.end(); it++ ){
  // cout << it->first << ':' << endl;
  // for (unsigned int i = 0; i < (it->second).size(); ++i){
  //     cout << (it->second).at(i) << endl;
  //   }
  // }
}

void Interpreter::evaluateQueries() {
  //queriez.at(0).toString();
  for (unsigned int i = 0; i < queriez.size(); ++i) {
    evalQuery(queriez.at(i));
  }

}

void Interpreter::evalRule(Rule rul) {
  vector<Predicate> predis = rul.getPredicates();
  vector<Relation> toJoin;

  rul.toString();

  for (unsigned int j = 0; j < predis.size(); ++j){
    map<string, int> variables1;
    vector<int> sameVars;
    map<string, vector<int>> variables;
    map<string,vector<int>> consts;
    vector<string> parameterz = (predis.at(j)).getParams();
    Relation newRel = db.find((predis.at(j)).getId())->second;
    for (unsigned int i = 0; i < parameterz.size(); ++i){
      if (((parameterz.at(i)).front() == '\'') && ((parameterz.at(i)).back() == '\'')) {
        //cout << parameterz.at(i) << endl;
        newRel.selectConst(parameterz.at(i), i);
        if (consts.find(parameterz.at(i)) != consts.end()) {
          consts[parameterz.at(i)].push_back(i);
        }
        else {
          consts.insert(pair<string, vector<int>>(parameterz.at(i), sameVars));
          consts[parameterz.at(i)].push_back(i);
        }
        //newRel.toString();
        //cout << endl;
      }
      else {
          variables1.insert(pair<string, int>(parameterz.at(i),i));
          //cout << "done 5";
          if (variables.find(parameterz.at(i)) != variables.end()) {
            variables[parameterz.at(i)].push_back(i);
          }
          else {
            variables.insert(pair<string, vector<int> >(parameterz.at(i),sameVars));
            variables[parameterz.at(i)].push_back(i);
          }
        }
    }

    map<string, vector<int>>::iterator it1;
    for (it1 = variables.begin(); it1 != variables.end(); it1++ ){
        if ((it1->second).size() > 1) {
          for (unsigned int i  = 0; i < (it1->second).size(); ++i) {
            //cout << (it1->second).at(i) << endl;
            sameVars.push_back((it1->second).at(i));
          }
          newRel.selectVar(sameVars);
          sameVars.clear();
        }
    }
    newRel.project(variables1);
    newRel.rename(variables1);
    toJoin.push_back(newRel);
    //newRel.toString();
  }


  Relation Result = toJoin.at(0);
  //Result.toString();
  map<string, int> indicies;
  // Join
  if (toJoin.size() > 1){
    for (unsigned int i = 1; i < toJoin.size(); ++i){
      map<string, int> Rel2indicies;
      Scheme attbs2= (toJoin.at(i)).getAttbs();
      for(unsigned int j = 0; j< attbs2.size(); ++j){
        Rel2indicies.insert(pair<string, int>(attbs2.at(j),j));
      }
      map<string, int>  Resultindicies;
      Scheme attbs1= Result.getAttbs();
      for(unsigned int j = 0; j< attbs1.size(); ++j){
        Resultindicies.insert(pair<string, int>(attbs1.at(j),j));
      }

      Result.combineSchemes(attbs2);
      //Result.toString();
      Result.combineTuples(Result.getTuples(), (toJoin.at(i)).getTuples(), Resultindicies, Rel2indicies);
      //Result.toString();
    }
  }

  //getting our project ready
  Scheme resultParamz = Result.getAttbs();
  vector<string> headParamz = (rul.getHeadPred()).getParams();
  map<string, int> columns;
  vector<int> order;

  for (unsigned int i = 0; i < headParamz.size(); ++i){
    for(unsigned int j = 0; j < resultParamz.size(); ++j){
      if(resultParamz.at(j) == headParamz.at(i)){
        columns.insert(pair<string, int>(resultParamz.at(j),j));
        order.push_back(j);
      }
    }
  }

  Result.project(columns, order);
  Result.rename(columns);
  //Result.toString();

  // Union
  (db.find((rul.getHeadPred().getId()))->second).unite(Result.getTuples());
}

void Interpreter::evaluateRules() {
  int numTuples = factz.size();
  bool newTuples = true;
  int iterations = 0;
  while(newTuples == true){
    for(unsigned int i = 0; i < rulez.size(); ++i){
      evalRule(rulez.at(i));
    }
    int actualTuples = 0;
    map<string, Relation>::iterator it1;
    for (it1 = db.begin(); it1 != db.end(); it1++ ){
      actualTuples += ((it1->second).getTuples()).size();
    }
    if (actualTuples == numTuples){
      newTuples = false;
    }
    else{
      numTuples += (actualTuples-numTuples);
    }

    ++iterations;
  }
  cout << endl;
  cout<< "Schemes populated after " << iterations << " passes through the Rules." << endl;
}


#endif
