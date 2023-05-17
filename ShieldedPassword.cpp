#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <fstream>


using namespace std;

    	   
string cifrar(const string& frase) {
    string cifrada = "";
    int desplazamiento = 23;

    for (char caracter : frase) {
        if (isalpha(caracter)) {
            // Obtiene el rango de valores de 'a' o 'A' según sea minúscula o mayúscula
            char inicio = islower(caracter) ? 'a' : 'A';
            // Aplica el desplazamiento, asegurándose de mantenerse dentro del rango de letras
            char cifrado = (caracter - inicio + desplazamiento) % 26 + inicio;
            cifrada += cifrado;
        } else {
            // Mantener los caracteres que no son letras sin cambios
            cifrada += caracter;
        }
    }

    return cifrada;
}

string descifrar(const string& fraseCifrada) {
    string descifrada = "";
    int desplazamiento = 23;

    for (char caracter : fraseCifrada) {
        if (isalpha(caracter)) {
            // Obtiene el rango de valores de 'a' o 'A' según sea minúscula o mayúscula
            char inicio = islower(caracter) ? 'a' : 'A';
            // Aplica el desplazamiento inverso para descifrar
            char descifrado = (caracter - inicio - desplazamiento + 26) % 26 + inicio;
            descifrada += descifrado;
        } else {
            // Mantener los caracteres que no son letras sin cambios
            descifrada += caracter;
        }
    }

    return descifrada;
}


int main(){
    sqlite3* db;
    
    int rc = sqlite3_open("Passwords.db", &db);

    if (rc != SQLITE_OK)
    {
        ofstream file;
        file.open("Passwords.db");
        file.close();
        string DBpassRAW;
        cout<<"Ingrese una contraseña para la base de datos: ";
        cin>>DBpassRAW;
        
        const char* sql_1 = "CREATE TABLE Passwords (_db_password TEXT NOT NULL, user TEXT NOT NULL DEFAULT [No Set], site TEXT NOT NULL DEFAULT [No Set], pass TEXT NOT NULL DEFAULT [No Set])";

		char* errMsg;
        rc = sqlite3_exec(db, sql_1, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            // Manejo de error en caso de que no se pueda crear la tabla
            fprintf(stderr, "Error SQL: %s\n", errMsg);
            sqlite3_free(errMsg);
            sqlite3_close(db);
            return 1;
        }							
    }


		while (bool login = false){
			system("cls");
			string loginPassRAW, _db_password;
			cout<<"Ingrese la contraseña de la base de datos: ";
			cin>>loginPassRAW;
			//Consultar _db_password
			if (loginPassRAW == _db_password){
				login = true;			
			}
		}

        system("cls");
        cout<<"Seleccione una opcion del menu: \n"
                "   [1] Ingresar nueva contrasena \n"
                "   [2] Ver contrasenas almacenadas \n"
                "   [3] Salir \n";
        int option;
        cin>>option;


    while (true) 
    {
        if(option == 1 or option == 2 or option == 3)
        {
            switch (option)
        	{
            case 1: 
                char pass[100], user[100], site[100];
	            cout<<"Ingrese el Usuario: "; cin.getline(user, 100);
	            cout<<"Ingrese el Sitio: "; cin.getline(site, 100);
                cout<<"Ingrese la Contraseña: "; cin.getline(pass,100);
                int i, j, length;
                length = strlen(pass);
            break;
            case 2: 
            	int option;
                
                //const char* siteRequest = sqlite3.exec();
                
                // TODO: Get Sites
                cout<<"Seleccione un Sitio para ver la contraseña: ";
                cin>>option; 
                return 0;
            break;
            case 3: return 0;
            break;
        	}
            
        }else{
            cout<<"[X] Ingrese un numero valido!!";
        }   
    }

    sqlite3_close(db);
    return 0;
}