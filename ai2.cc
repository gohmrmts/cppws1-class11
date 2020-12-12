#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

vector<string> bufs;
bool flag;

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

void makeSentence(string character, string line)
{
  vector<string> nextChar;
  for (int i =0; i  < bufs.size(); i++)
  {
    string tmp = bufs.at(i);
    if (character == tmp.substr(0, countByte(tmp[0])))
    {
      nextChar.push_back(bufs.at(i));
    }
  }
  int total = nextChar.size();
  sort(nextChar.begin(), nextChar.end());
  nextChar.erase(unique(nextChar.begin(), nextChar.end()), nextChar.end());
  int count[nextChar.size()];
  for (int i = 0; i < nextChar.size(); i++)
  {
    count[i] = 0;
    for (int j = 0; j < bufs.size(); j++)
    {
      if (nextChar.at(i) == bufs.at(j))
      {
        count[i]++;
      }
    }
    string tmp = nextChar.at(i);
    nextChar.at(i) = tmp.substr(countByte(tmp[0]), countByte(tmp[countByte(tmp[0])]));
  }
  srand(time(NULL));
  int r = rand() % total;
  for (int i = 1; i < nextChar.size(); i++)
  {
    count[i] = count[i] + count[i - 1];
    if (r < count[i])
    {
      line += nextChar.at(i);
      if (nextChar.at(i) != "。")
      {
        makeSentence(nextChar.at(i), line);
      }
      else
      {
        cout << line << endl;
        flag = true;
        break;
      }
    }
    if (flag)
    {
      break;  
    }
//    cout << nextChar.at(i) << endl;
//    cout << count[i] << endl;
  }
}

int main()
{
  const char* fname = "2-gram.txt";

  ifstream ifs(fname);
  if (!ifs)
  {
    cerr << "Cannnot open file" << fname << endl;
    exit(1);
  }

  string buf;
  getline(ifs, buf);
  while (!ifs.eof())
  {
    bufs.push_back(buf);
    getline(ifs, buf);
  }

  vector<string> none = bufs;

  string line;
  cout << "input" << endl;
  getline(cin, line);

  srand(time(NULL));
  int r = rand() % line.size();
  line.substr(countByte(line[r]), countByte(line[countByte(line[r])]));
  
  
  string character = line.substr(countByte(line[r]), countByte(line[countByte(line[r])]));
  makeSentence(character, character);
}
