# TP1-OrgaDeCompus

## Link del informe

https://www.overleaf.com/9647369997jztxtwzjwqjm

## Comando para crear un video con ffmpeg

Ejecutando el archivo glider, especificando la salida como `salida`

```shell
ffmpeg -start_number 0 -i salida_%03d.pbm -vcodec mpeg4 salida.avi

```

Creamos el video usando ffmpeg con el siguiente comando

```shell
ffmpeg -start_number 0 -i salida_%03d.pbm -vcodec mpeg4 salida.avi

```
