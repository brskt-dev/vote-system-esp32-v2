# 
# Requisitos de montagem:
# ESP32 Dev Module e cabo USB, 2x LED Difuso 5mm, 2x Sensor Infravermelho Reflexivo de Obstáculo, Sensor Ultrassonico HC-SR04, Cabos Jumper macho-macho, Protoboard.
#
# A integração com Firebase é opcional e pode ser adaptada para outros bancos de dados ou API's.
#
# Funcionamento:
# O núcleo 0 da placa trabalha com a leitura dos sensores e os condiciona as regras de leitura.
# O núcleo 1 é responsável por receber os dados lidos pelo núcleo 0 e importá-los ao banco de dados.
