#!/bin/bash

# Actualizar el índice de paquetes
sudo apt update

# Instalar Java (necesario para Elasticsearch y Kibana)
sudo apt install -y default-jre

# Importar la clave pública de Elasticsearch y agregar el repositorio de paquetes
wget -qO - https://artifacts.elastic.co/GPG-KEY-elasticsearch | sudo apt-key add -
echo "deb https://artifacts.elastic.co/packages/7.x/apt stable main" | sudo tee /etc/apt/sources.list.d/elastic-7.x.list

# Actualizar el índice de paquetes
sudo apt update

# Instalar Elasticsearch, Kibana y Logstash
sudo apt install -y elasticsearch kibana logstash

# Configurar Elasticsearch y Kibana para que se inicien automáticamente en el arranque del sistema
sudo systemctl enable elasticsearch.service
sudo systemctl enable kibana.service

# Iniciar Elasticsearch, Kibana y Logstash
sudo systemctl start elasticsearch.service
sudo systemctl start kibana.service
sudo systemctl start logstash.service
