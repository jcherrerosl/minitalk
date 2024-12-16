# minitalk

Este proyecto es una implementación del proyecto "minitalk" de 42, que permite la comunicación entre procesos mediante señales en C.    

## Descripción

Minitalk es una pequeña aplicación que permite enviar mensajes de texto desde un cliente a un servidor utilizando señales UNIX. Este proyecto forma parte del currículo de la escuela 42 y está diseñado para enseñar a los estudiantes sobre la manipulación de señales y la comunicación entre procesos en sistemas UNIX.    

## Instalación

Para instalar y compilar el proyecto, sigue estos pasos:    

```bash
git clone https://github.com/jcherrerosl/minitalk.git
cd minitalk
make
```
Con este comando, se crearán dos programas ejecutables: `server` y `client`.   

Para iniciar el servidor:   
```bash
./server
```
Para enviar un mensaje desde el cliente al servidor:   
```bash
./client <PID> <mensaje>
```

