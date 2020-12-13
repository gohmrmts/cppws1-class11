#include <fstream>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<string> ngramed;
vector<string> txt;
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

int countChar(string line)
{
  int num = 0;
  int i = 0;
  while(line[i] != '\0')
  {
    i += countByte(line[i]);
    num++;
  }
  return num;
}

void ngram(string line, int n)
{
  int numChar = countChar(line);
  int count  = 0;

  if (numChar >= n)
  {
    for (int i = 0; i < line.size(); i += countByte(line[i]))
    {
      if (count <= numChar - n)
      {
        count++;
        string tmp;
        for(int j = 0; j < n; j++)
        {
          // cout << line.substr(i + j * (countByte(line[i])), countByte(line[i]));
          tmp += line.substr(i + j * (countByte(line[i])), countByte(line[i]));
        }
        ngramed.push_back(tmp);
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    // cout << line << endl;
  }
}

int judgeMorpheme(unsigned char c1, unsigned char c2, unsigned char c3)
{
  int flag = 0;
  if (c1 == 0xe3)
  {
    if((c2 >= 0x82) && (c3 >= 0xa1))
    {
      if ((c2 <= 0x83) && (c3 <= 0xb6))
      {
        flag = 1; // カタカナ
      }
    }
    else if((c2 >= 0x81) && (c3 >= 0x81))
    {
      flag = -1; // ひらがな
    }
    else if ((c2 <= 0x82) && (c3 <= 0x96))
    {
      flag = -1; // ひらがな
    }
  }
  else if (c1 == 0xe4)
  {
    if(c2 <= 0xb8)
    {
      if (c3 <= 0x80)
      {
        flag = 1; // ひらがな
      }
    }
  }
  return flag;
}

void morpheme()
{
  string word = "";
  int beforeJudge = 5; // 0, 1, -1以外の何でもない数
  bool flag_same = false;
  for (int i = 0; i < ngramed.size(); i++)
  {
    int judge = judgeMorpheme(ngramed.at(i)[0], ngramed.at(i)[1], ngramed.at(i)[2]);
    if(countByte(ngramed.at(i)[0]) == 3)
    {
      if (beforeJudge == judge)
      {
        flag_same = true;
        word += ngramed.at(i);
        if ( i <= ngramed.size() - 2 && judge ==  judgeMorpheme(ngramed.at(i + 1)[0], ngramed.at(i + 1)[1], ngramed.at(i + 1)[2]))
        {
          continue;
        }
      }
      else
      {
        beforeJudge = judge;
        word = ngramed.at(i);
        flag_same = false;
        if ( i <= ngramed.size() - 2 && judge ==  judgeMorpheme(ngramed.at(i + 1)[0], ngramed.at(i + 1)[1], ngramed.at(i + 1)[2]))
        {
          continue;
        }
      }
    }
    else
    {
      if (beforeJudge == 4)
      {
        flag_same = true;
        word += ngramed.at(i);
        if ( i <= ngramed.size() - 2 && judge ==  judgeMorpheme(ngramed.at(i + 1)[0], ngramed.at(i + 1)[1], ngramed.at(i + 1)[2]))
        {
          continue;
        }
      }
      else 
      {
        beforeJudge = judge;
        word = ngramed.at(i);
        flag_same = false;
        if ( i <= ngramed.size() - 2 && judge ==  judgeMorpheme(ngramed.at(i + 1)[0], ngramed.at(i + 1)[1], ngramed.at(i + 1)[2]))
        {
          continue;
        }
      }
    }
    txt.push_back(word);
    if ( i <= ngramed.size() - 2 && judge == 0)
    {
      int nextJudge = judgeMorpheme(ngramed.at(i + 1)[0], ngramed.at(i + 1)[1], ngramed.at(i + 1)[2]);
      if (nextJudge == -1)
      {
        if ( ngramed.at(i + 1) == "い" )
        {
          adj.push_back(word + "い");
        }
        else if ( ngramed.at(i + 1) == "う" )
        {
          verb.push_back(word + "う");
        }
        else if ( ngramed.at(i + 1) == "だ" )
        {
          adjv.push_back(word + "だ");
        }
        else
        {
          noun.push_back(word);
        }
      }
    }
  }
}

string sel_noun()
{
  srand( time( NULL ) );
  vector<string> sel_noun;

  int r = rand() % noun.size();

  return noun.at(r);
}

string sel_prase()
{
  if ( verb.empty() && adj.empty() && adjv.empty() )
  {
    return "FAILED";
  }
  int r = rand() % 3;
  vector<string> sel_prase;
  switch(r)
  {
    case 0:
      if ( !verb.empty() )
      {
        r = rand() % verb.size();
        return verb.at(r);
      }
    case 1:
      if ( !adj.empty() )
      {
        r = rand() % adj.size();
        return adj.at(r);
      }
    case 2:
      if ( !adjv.empty() )
      {
        r = rand() % adjv.size();
        return adjv.at(r);
      }
  }
  return "ERROR";
}

int main()
{
  string line;
  cout << "input :";
  cin >> line;

  ngram(line, 1);

  morpheme();

  string noun = sel_noun();
  string prase = sel_prase();
  if ( prase == "ERROR" )
  {
    while ( prase == "ERROR" )
    {
      prase = sel_prase();
    }
  }

  if ( prase == "FAILED" )
  {
    cout << prase << " : Cannot generate sentence." << endl;
  }
  else
  {
    cout << noun << "は" << prase << endl;
  }

}
