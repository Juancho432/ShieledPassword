#include <iostream>
#include <stdio.h>
#include "sha256.h"
#include "sqlite3.h"
#include <filesystem>
#include <fstream>


using namespace std;
namespace fs = std::filesystem;


static int createDB(const char* s);
static int createTable(const char* s);


int main()
{
    string dir = fs::current_path().string();
    fs::path databaseDir = fs::path(dir) / "Passwords.db";
    sqlite3* db;
    
    int rc = sqlite3_open("Passwords.db", &db);

    if (rc != SQLITE_OK)
    {
        ofstream file;
        file.open("Passwords.db");
        file.close();
    }

        system("cls");
        cout<<"Seleccione una opcion del menu: \n"
                "   [1] Ingresar nueva contraseña \n"
                "   [2] Ver contraseñas almacenadas \n"
                "   [3] Salir \n";
        int option;
        cin>>option;


    while (true) 
    {
        if(option == 1 or option == 2 or option == 3)
        {
            switch (option)
        {
            case 1: //newPassword();
            break;
            case 2: //viewPassword();
            break;
            case 3: return 0;
        
        }
            
        }else{
            cout<<"[X] Ingrese un numero valido!!";
        }   
    }

    sqlite3_close(db);
    return 0;
}

