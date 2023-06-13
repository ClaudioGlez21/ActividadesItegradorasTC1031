#ifndef REGISTRO_H
#define REGISTRO_H
#include <iostream>
#include <string>

class Registro {
public:
        // Constructores
        Registro();
        Registro(std::string mes, std::string dia, std::string hora, std::string ip, std::string razon);

        // Getters
        std::string getMes();
        std::string getDia();
        std::string getHora();
        std::string getIp();
        std::string getRazon();

        // Setters
        void setMes(std::string mes);
        void setDia(std::string dia);
        void setHora(std::string hora);
        void setIp(std::string ip);
        void setRazon(std::string razon);

        // Sobrecarga de de operador de flujo de entrada
        friend std::istream &operator>>(std::istream &, Registro &);
        // Sobrecarga de operador de flujo de salida
        friend std::ostream &operator<<(std::ostream &, const Registro &);
        // Sobrecarga del operador booleano < como funcion de la clase
        bool operator<(const Registro &) const;
        // Sobrecarga del operador booleano <= como funcion de la clase
        bool operator<=(const Registro &) const;

private:
        std::string mes;
        std::string dia;
        std::string hora;
        std::string ip;
        std::string razon;
};

#endif // REGISTRO_H