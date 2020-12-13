#include <fstream>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<string> noun;
vector<string> verb;
vector<string> adj;
vector<string> adjv;

int countByte(unsigned char c)
{
  int byte = 0;
  if((c >= 0x00) && (c <= 0x7f))
  {
    byte = 1;
  }
  else if((c >= 0xc2) && (c <= 0xdf))
  {
    byte = 2;
  }
  else if((c >= 0xe0) && (c <= 0xef))
  {
    byte = 3;
  }
  else if((c >= 0xf0) && (c <= 0xf7))
  {
    byte = 4;
  }
  else if((c >= 0xf8) && (c <= 0xfb))
  {
    byte = 5;
  }
  else if((c >= 0xfc) && (c <= 0xfd))
  {
    byte = 6;
  }
  return byte;
}

string sel_noun( string word )
{
  srand( time( NULL ) );
  string line;
  ifstream ifs_noun("noun.txt");
  if ( !ifs_noun )
  {
    cerr << "failed open noun.txt" << endl;
    exit(1);
  }
  getline( ifs_noun, line );
  while( !ifs_noun.eof() )
  {
    noun.push_back( line );
    getline( ifs_noun, line );
  }

  vector<string> sel_noun;

  for ( int i = 0; i < noun.size(); i++ )
  {
    if ( word == noun.at(i).substr(0, countByte(noun.at(i)[0])) )
    {
      sel_noun.push_back( noun.at(i) );
    }
  }

  int r = rand() % sel_noun.size();

  ifs_noun.close();
  return sel_noun.at(r);
}

string sel_prase()
{
  string line;
  int r = rand() % 3;
  const char* fname;
  switch(r)
  {
    case 0:
      fname = "verb.txt";
      break;
    case 1:
      fname = "adj.txt";
      break;
    case 2:
      fname = "adjv.txt";
      break;
  }
  ifstream ifs(fname);
  if ( !ifs )
  {
    cerr << "failed open " << fname << endl;
    exit(1);
  }
  vector<string> sel_prase;
  getline( ifs, line );
  while( !ifs.eof() )
  {
    sel_prase.push_back( line );
    getline( ifs, line );
  }
  r = rand() % sel_prase.size();

  ifs.close();
  return sel_prase.at(r);
}

int main()
{
  string word;
  cout << "input :";
  cin >> word;

  cout << sel_noun(word);
  cout << "は";
  cout << sel_prase();
}
