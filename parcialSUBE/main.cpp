/*
Autor: GAB
Fecha: 08/04/19
Comentario:
*/

# include<iostream>
# include<cstdlib>
# include<cstdio>
# include<cstring>

using namespace std;

struct fecha{
  int dia, mes, anio;
  };

struct medio{
    int col;
    int sub;
    int tren;
};

struct usuario{
    char dni[10];
  char apellido[20];
  char nombre[20];
  char direccion[30];
  int cp;
  int cardnum;
  int viajesrealizados;
    struct fecha fechaalta;
    float saldo;
  bool estado;
    int numviaje;
    struct medio transporte;
    struct fecha fechaviaje;
    float importe;
};

struct usuario leerRegistroUsuario(int);
int buscarRegistroUsuario(char *dni);
bool grabarRegistroUsuario(struct usuario, int);
void mostrarRegistroUsuario(struct usuario);
struct usuario cargarRegistroUsuario();
struct usuario modifRegistroUsuario(struct usuario &re);

void altaUsuario();
void bajaLogicaUsuario();
void modificacionUsuario();
bool listadoUsuarios();
void reiniciarArchivo();

int main(){
  int opc;
  while(1){
    system("cls");
    cout<<"MENU USUARIOS"<<endl;
    cout<<"1. ADD USER"<<endl;
    cout<<"2. BAJA LOGICA"<<endl;
    cout<<"3. MODIFY USER"<<endl;
    cout<<"4. LISTADO USERS"<<endl;
    cout<<"5. REINICIAR ARCHIVO"<<endl;
    cout<<"6. FIN DEL PROGRAMA"<<endl;
    cout<<"OPCION: ";
    cin>>opc;
    system("cls");
    switch(opc){
      case 1:
            altaUsuario();
            break;
      case 2:
            bajaLogicaUsuario();
            break;
      case 3:
            modificacionUsuario();
            break;
      case 4:
            if(!listadoUsuarios()){
              cout<<"NO HAY REGISTRO PARA LISTAR"<<endl;
            }
                system("cls"); //LIMPIA LA PANTALLA ANTES DE MOSTRAR LOS REGISTROS(cuando se ejecuta el CASE 4, se muestra dos veces el registro por algún motivo)
                  listadoUsuarios();
            break;
        case 5:
            reiniciarArchivo();
            break;
      case 6:
            return 0;
            break;
      default: cout<<"OPCION INCORRECTA"<<endl;
            break;
      }

    system("pause");
  }
  return 0;
}
/////////////////////////////////

void altaUsuario(){
  struct usuario reg;
  reg=cargarRegistroUsuario();
  int pos=buscarRegistroUsuario(reg.dni);
  if(pos!=-1){
    cout<<"EL USUARIO YA EXISTE"<<endl;
    return;
  }
  if(grabarRegistroUsuario(reg, pos)){
    cout<<"REGISTRO AGREGADO"<<endl;
    }
  else{
    cout<<"NO SE PUDO AGREGAR EL REGISTRO";
    }
  system("pause");
}

struct usuario cargarRegistroUsuario(){
  struct usuario reg;
  system("cls");
  cout<<"DNI: ";
  cin>>reg.dni;
  cout<<"APELLIDO: ";
  cin>>reg.apellido;
  cout<<"NOMBRE: ";
  cin>>reg.nombre;
  cout<<"DIRECCION: ";
  cin>>reg.direccion;
  cout<<"CODIGO POSTAL: ";
  cin>>reg.cp;
  cout<<"NUMERO DE TARJETA: ";
  cin>>reg.cardnum;
  cout<<"FECHA DE ALTA: DIA:";
  cin>>reg.fechaalta.dia;
    cout<<"FECHA DE ALTA: MES:";
  cin>>reg.fechaalta.mes;
    cout<<"FECHA DE ALTA: ANIO:";
  cin>>reg.fechaalta.anio;
  cout<<"SALDO: ";
  cin>>reg.saldo;
  reg.estado=true;
  cout<<"NUMERO DE VIAJES HASTA EL MOMENTO: ";
  cin>>reg.numviaje;
  cout<<"INDIQUE MEDIO DE TRANSPORTE: ";
  cout<<"1-Colectivo | 2-Subte | 3-Tren"<<endl;
  int m=0;
  cin>>m;
  cout<<"FECHA DEL VIAJE: DIA:";
  cin>>reg.fechaviaje.dia;
    cout<<"FECHA DEL VIAJE: MES:";
  cin>>reg.fechaviaje.mes;
    cout<<"FECHA DEL VIAJE: ANIO:";
  cin>>reg.fechaviaje.anio;
  if(reg.fechaviaje.anio==2018){
  switch(m)
  {
      case 1: reg.transporte.col++; break;
      case 2: reg.transporte.sub+=2; break;
      case 3: reg.transporte.tren+=3; break;
      default: cout<<" "<<endl; break;
  }
  }
  cout<<"IMPORTE DEL VIAJE: ";
  cin>>reg.importe;
  return reg;
  }

  void modifRegistroUsuario(struct usuario &reg, int pos){
      FILE *p;
    p=fopen("usuario.dat","rb+");
    if(p==NULL){cout<<"ERROR"<<endl;}
    else{
    fseek(p, pos*sizeof reg,0);
  reg=cargarRegistroUsuario();
    if(grabarRegistroUsuario(reg, pos)){
    cout<<"REGISTRO MODIFICADO"<<endl;
    }
  else{
    cout<<"NO SE PUDO MODIFICAR EL REGISTRO";
    }
  system("pause");
}
  };

void mostrarRegistroUsuario(struct usuario reg){
  if(reg.estado){
    cout<<"-----------------------------------------"<<endl;
    cout<<"DNI: ";
  cout<<reg.dni<<endl;
  cout<<"APELLIDO: ";
  cout<<reg.apellido<<endl;
  cout<<"NOMBRE: ";
  cout<<reg.nombre<<endl;
  cout<<"DIRECCION: ";
  cout<<reg.direccion<<endl;
  cout<<"CODIGO POSTAL: ";
  cout<<reg.cp<<endl;
  cout<<"NUMERO DE TARJETA: ";
  cout<<reg.cardnum<<endl;
  cout<<"FECHA DE ALTA: ";
  cout<<reg.fechaalta.dia<<"/";
  cout<<reg.fechaalta.mes<<"/";
  cout<<reg.fechaalta.anio<<endl;
  cout<<"SALDO: ";
  cout<<reg.saldo<<endl;
  reg.estado=true;
  cout<<"NUMERO DE VIAJES HASTA EL MOMENTO: ";
  cout<<reg.numviaje<<endl;
  cout<<"CANTIDAD DE VIAJES EN CADA MEDIO DE TRANSPORTE: ";
  cout<<"COLECTIVO: "<<reg.transporte.col<<endl;
  cout<<"SUBTE: "<<reg.transporte.sub<<endl;
  cout<<"TREN: "<<reg.transporte.tren<<endl;
  cout<<"FECHA DEL VIAJE: ";
  cout<<reg.fechaviaje.dia<<"/";
  cout<<reg.fechaviaje.mes<<"/";
cout<<reg.fechaviaje.anio<<endl;
  cout<<"IMPORTE DEL VIAJE: ";
  cout<<reg.importe<<endl;
  }
}

bool grabarRegistroUsuario(struct usuario reg, int pos){
  FILE *p;
  if(pos<0){
    p=fopen("usuario.dat","ab");
    if(p==NULL){return false;}
  }
  else{
    p=fopen("usuario.dat","rb+");
    if(p==NULL){return false;}
    fseek(p, pos*sizeof reg,0);
  }
  bool grabo=fwrite(&reg, sizeof reg, 1, p);
  fclose(p);
  return grabo;
}

int buscarRegistroUsuario(char *dni){
  FILE *p;
  struct usuario reg;
  int pos=0;
  p=fopen("usuario.dat","rb");
  if(p==NULL){return -1;}
  while(fread(&reg, sizeof reg, 1, p)==1){
    if(strcmp(reg.dni,dni)==0){
      fclose(p);
      return pos;
      }
    pos++;
    }
  fclose(p);
  return -1;
}


void bajaLogicaUsuario(){
  char dni[10];
  struct usuario reg;
  int pos;
  //PEDIR EL DNI DEL USUARIO A ELIMINAR
  cout<<"INGRESE EL DNI DEL USUARIO A DAR DE BAJA: ";
  cin>>dni;
  pos=buscarRegistroUsuario(dni);
  if(pos==-1){
    cout<<"NO EXISTE EL USUARIO"<<endl;
    return;
    }
  reg=leerRegistroUsuario(pos);
  reg.estado=false;
  if(grabarRegistroUsuario(reg,pos)){
    cout<<"REGISTRO ELIMINADO"<<endl;
    }
  else{
    cout<<"NO SE PUDO ELIMINAR EL REGISTRO"<<endl;
    }
  }

void modificacionUsuario(){
    char dni[10];
  struct usuario reg;
  int pos;
  //PEDIR EL DNI DEL USUARIO A MODIFICAR
  cout<<"INGRESE EL DNI DEL USUARIO A MODIFICAR: ";
  cin>>dni;
  pos=buscarRegistroUsuario(dni);
  if(pos==-1){
    cout<<"NO EXISTE EL USUARIO"<<endl;
    return;
    }
    else
    {
 system("cls");
 cout<<"A CONTINUACION, INGRESE LOS NUEVOS DATOS DEL USUARIO:"<<endl;
 system("pause");
  reg=leerRegistroUsuario(pos);
  modifRegistroUsuario(reg, pos);
    }
   system("pause");
}

bool listadoUsuarios(){
  FILE *p;
  struct usuario reg;
  p=fopen("usuario.dat","rb");
  if(p==NULL){return false;}
  while(fread(&reg, sizeof reg, 1, p)==1){
    mostrarRegistroUsuario(reg);
    cout<<" "<<endl;
    }
  fclose(p);
  return true;
}


struct usuario leerRegistroUsuario(int pos){
  FILE *p;
  struct usuario reg;
  strcpy(reg.dni, "nada");
  p=fopen("usuario.dat","rb");
  if(p==NULL)return reg;
  fseek(p, sizeof reg*pos, 0);
  fread(&reg, sizeof reg, 1, p);
  fclose(p);
  return reg;
 }


 void reiniciarArchivo(){
 FILE *p;
 p=fopen("usuario.dat","wb");
 cout<<"ARCHIVO REINICIADO"<<endl;
  cout<<"SE HAN ELIMINADO TODOS LOS REGISTROS"<<endl;
 fclose(p);
 };
