#include <fstream>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<string> noun;
vector<string> verb;
vector<string> adj;
vector<string> adjv;

string sel_noun( string word )
{
  srand(time(null));
  string line;
  ifstream ifs_noun("noun.txt");
  if ( ifs_noun )
  {
    cerr << "failed open noun.txt" << endl;
    exit(1);
  }
  getline( ifs_noun, line );
  while( !ifs_noun.eof() )
  {
    noun.push_back( line );
    getline( ifs, line );
  }

  vector<string> sel_noun;

  for ( int i = 0; i < noun.size(); i++ )
  {
    if ( word == noun.at(i) )
    {
      sel_noun.push_back( noun.at(i) );
    }
  }


  
}

int main()
{
  ifstream ifs_verb("verb.txt");
  ifstream ifs_adj("adj.txt");
  ifstream ifs_adjv("adjv.txt");
  
  string word;
  cout << "input :";
  cin >> word;


  


}
