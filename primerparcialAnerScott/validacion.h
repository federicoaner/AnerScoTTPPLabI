#ifndef VALIDACION_H_INCLUDED
#define VALIDACION_H_INCLUDED



#endif // VALIDACION_H_INCLUDED
int utn_getEntero(int* pEntero,int reintentos,char* msg,char*msgError,int min,int max);

int utn_getFlotante(float*pFloat,int reintentos,char* msg,char*msgError,float min,float max);
int getCadena(char* pAux,int limite);
int getInt(int* pAux);
int isInt(char *pAux);
int isFloat(char* pAux);
int getFloat(float*pAux);
int utn_getCadena(char *pAux,int limite,int reintentos,char* msj,char*msjError);
int isLetras(char*pAux);
int validateFlag(int* flag, char* msgError);
int validarMail(char *pAux);
int utn_getEmail(char* pString, int limite, int reintentos, char* msg, char* msgError);


//utn_getCadena(auxOrquesta.nombre,51,2,"Ingrese el nombre: ","\nError. Reingrese el nombre\n");
//utn_getCadena(auxOrquesta.lugar,51,2,"Ingrese el lugar: ","\nError. Reingrese el lugar\n");
