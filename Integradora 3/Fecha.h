#ifndef FECHA_H
#define FECHA_H
#include <iostream>
#include <string>

// Complejidad: O(1)  Complejidad de todo el archivo

class Fecha 
{
    public:
        // Constructores
        Fecha();
        Fecha(std::string mes, std::string dia, std::string hora);

        // Getters
        std::string getMes();
        std::string getDia();
        std::string getHora();

        // Setters
        void setMes(std::string mes);
        void setDia(std::string dia);
        void setHora(std::string hora);

        // Sobrecargas
        // Sobrecarga de de operador de flujo de entrada
        friend std::istream &operator>>(std::istream &, Fecha &);
        // Sobrecarga de operador de flujo de salida
        friend std::ostream &operator<<(std::ostream &, const Fecha &);
        // Sobrecarga del operador booleano < como funcion de la clase
        bool operator<(const Fecha &) const;
        // Sobrecarga del operador booleano <= como funcion de la clase
        bool operator<=(const Fecha &) const;
    private:
        std::string mes;
        std::string dia;
        std::string hora;
};

#endif // FECHA_H