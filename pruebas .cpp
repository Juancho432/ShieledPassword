#include <iostream>
#include <fstream>
using namespace std;
int main()
{
  ofstream file;
  file.open("Passwords.txt");
  file << "primera línea\n";
  file << "segunda línea\n";
  file << "tercera línea\n";
  file.close();
  return 0;
}