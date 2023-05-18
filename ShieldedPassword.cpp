#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <fstream>


using namespace std;


int callback(void* NotUsed, int argc, char** argv, char** azColName){
    for (int i = 0; i < argc; i++){
        cout<<azColName[i] <<": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    return 0;
}

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

int newPassword(sqlite3* db, int rc){
    string passRAW, user, site;
	cout<<"Ingrese el Usuario: "; 
    cin>>user;
	cout<<"\nIngrese el Sitio: "; 
    cin>>site;
    cout<<"\nIngrese la Contraseña: "; 
    cin>>passRAW;
                
    string passCifrada = cifrar(passRAW);
    string setUser = "UPDATE Passwords SET user = '" + user + "';";
    string setSite = "UPDATE Passwords SET site = '" + site + "';";
    string setPass = "UPDATE Passwords SET pass = '" + passCifrada + "';";

    cout<<"Contraseña guardada!!"<<endl;
    rc = sqlite3_exec(db, setUser.c_str(), 0, 0, 0);
    return 0;
}

int viewPasswords(sqlite3* db, int rc){
    const char *sql = "SELECT site FROM Passwords;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    
    while (sqlite3_step(stmt)== SQLITE_ROW){
        const char *valor = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        cout<< valor <<endl;
    }

    string option;
    cout<<"Ingrese el sitio de la contraseña: ";
    cin>>option;

    string resultSQL = "SELECT user, pass FROM Passwords WHERE site = '" + option + "';";
    char* zErrMsg;
    rc = sqlite3_exec(db, resultSQL.c_str(), callback, 0, &zErrMsg);


    return 0;

}

int main(){
    sqlite3* db;
    int rc;
    ifstream database;
    database.open("Passwords.db");

    if (database){
        rc = sqlite3_open("Passwords.db", &db);
    }else{
        cout<<"Creando Base de Datos..."<<endl;
        ofstream file;
        file.open("Passwords.db");
        file.close();
        
        rc = sqlite3_open("Passwords.db", &db);
        cout<<"Configurando Base de Datos...."<<endl;
        const char* sql_1 = "CREATE TABLE Passwords (user TEXT NOT NULL, site TEXT NOT NULL, pass TEXT NOT NULL)";
        
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
    
    init:

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Seleccione una opcion del menu: \n"
                "   [1] Ingresar nueva contrasena \n"
                "   [2] Ver contrasenas almacenadas \n"
                "   [3] Salir \n";

               
        int option;
        numErr: 
        cin>>option;
        

        if(option == 1 or option == 2 or option == 3)
        {
            switch (option)
        	{
            case 1: 
                newPassword(db, rc);
                goto init;
                break;
            case 2: 
                viewPasswords(db, rc);
                goto init;            	
                break;
            case 3: 
                sqlite3_close(db);
                cout<<"[X] Saliendo...";
                return 0;
                break;
        	}
            
        }else{
            cout<<"[X] Ingrese un numero valido!! \n";
            goto numErr;
        }   
    
}