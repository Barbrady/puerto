#!/bin/bash

# Verificar que se está ejecutando con permisos de superusuario
if [[ $(id -u) -ne 0 ]]; then
  echo "Este script debe ser ejecutado con permisos de superusuario (root)."
  exit 1
fi

# Verificar que se recibió el nombre de usuario como argumento
if [[ $# -ne 1 ]]; then
  echo "Uso: $0 <nombre_de_usuario>"
  exit 1
fi

# Asignar el nombre de usuario a una variable
USER=$1

# Generar un password aleatorio
PASSWORD=$(date +%s | sha256sum | base64 | head -c 32 ; echo)

# Configurar el usuario en Elasticsearch
echo "Configurando usuario $USER en Elasticsearch..."
/usr/share/elasticsearch/bin/elasticsearch-users useradd $USER -p $PASSWORD -r superuser

# Mostrar el nombre de usuario y el password generado
echo "Usuario: $USER"
echo "Password: $PASSWORD"
