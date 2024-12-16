# minitalk

Este proyecto es una implementación del proyecto "minitalk" de 42, que permite la comunicación entre procesos mediante señales en C.    

## Descripción

Minitalk es una pequeña aplicación que permite enviar mensajes de texto desde un cliente a un servidor utilizando señales UNIX. Este proyecto forma parte del currículo de la escuela 42 y está diseñado para enseñar a los estudiantes sobre la manipulación de señales y la comunicación entre procesos en sistemas UNIX.    

## Detalles del programa

La complejidad de la aplicación radica en que únicamente se utilizan las señales SIGUSR1 y SIGUSR2. Estas señales están abiertas para que el usuario asigne significados específicos a cada una. En nuestro caso, hemos decidido utilizar SIGUSR1 para representar el bit 1 y SIGUSR2 para representar el bit 2. 

### Conversión y Decodificación de Mensajes

Para enviar un mensaje, primero se convierte el texto a su representación binaria. Cada carácter del mensaje se transforma en una secuencia de bits, que luego se envían como señales al servidor. El servidor recibe estas señales, las decodifica de vuelta a su representación binaria y finalmente reconstruye el mensaje original.

Por ejemplo, la letra 'A' se convierte en `01000001` en binario. Para enviar 'A', el cliente enviará una secuencia de señales: SIGUSR2, SIGUSR1, SIGUSR2, SIGUSR2, SIGUSR2, SIGUSR2, SIGUSR2, SIGUSR1.

## Instalación

Para instalar y compilar el proyecto, sigue estos pasos:    

```bash
git clone https://github.com/jcherrerosl/minitalk.git
cd minitalk
make
```
Con este comando, se crearán dos programas ejecutables: `server` y `client`.   

## Uso

Para iniciar el servidor:   
```bash
./server
```
Para enviar un mensaje desde el cliente al servidor:   
```bash
./client <PID> <mensaje>
```
