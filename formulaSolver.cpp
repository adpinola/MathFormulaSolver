#include "formulaSolver.h"
using namespace std;
// ejemplo de formula
// (A + B * C + D ) / ( E - F / G - I ) + ( J / K + L )
// La formula se separa en terminos y cada uno con su operador formara parte de un nodo
// Los nodos son operaciones + - * / conpuestas por dos terminos
// Para el ejemplo mostrado, el arbol se forma de la forma expuesta a continuacion
//
//                        /
//               A+B*C+D     (E-F/G-I)+(J/K+L)
//          +                         +
//        A   B*C+D         E-F/G-I        J/K+L
//              +              -             +
//           B*C   D        E    F/G-I   J/K   L
//            +                    -      /
//          B   C              F/G   I  J   K
//                              /
//                            F   G
//
// Cada nodo contiene un operador y apunta a los dos terminos en los que se aplica ese operador
// cuando se apunta a terminos NULL (y el operador sera tambien NULL) estamos ante una variable
// claramente definida cuyo valor se obtiene directamente del mapa de variables.
const char operators[OPERATOR_PRIORITY_LEVELS][2] = {
    {'+', '-'},
    {'*', '/'}};

void ReplaceStringInPlace(std::string &subject, const std::string &search,
                          const std::string &replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

// addVariable: Agrega al mapa de variables para calcular el resultado de la formula
//              la variable con el nombre indicado @nombre y del valor @valor
// Se quitan todos los espacios en blanco y se reemplazan por "_"
// Caracteres validos son solo letras y numeros, los incorrectos seran reemplazados por "_"
void Formula::addVariable(string nombre, float valor)
{
    ReplaceStringInPlace(nombre," ", "_");
    for (auto itr = nombre.begin(); itr != nombre.end(); ++itr)
    {
        if ( (*itr) < '0' || ((*itr) > '9' && (*itr) < 'A') || ((*itr) > 'Z' && (*itr) < 'a') || (*itr) > 'z')
            *itr = '_';
    }
    variable.insert(pair<string, float>(nombre, valor));
}

void Formula::showVariables()
{
    map<string, float>::iterator itr;
    for (itr = variable.begin(); itr != variable.end(); ++itr)
    {
        cout << itr->first << "=" << itr->second << endl;
    }
}

void Formula::Parse(string ecuacion)
{
    // En primer lugar voy a elminar todos los espacios en blancos.
    if (!root)
    {
        root = new eqNode;
        root->left = NULL;
        root->right = NULL;
    }
    ReplaceStringInPlace(ecuacion, " ", "");
    Parse(ecuacion, root);
}

void Formula::Parse(string ecuacion, eqNode *nodo)
{
    int n_parentesis = 0;
    int n_pos = 0;
    bool operator_found = false;
    // Verifico si puedo quitar los parentesis de los extremos
    if (ecuacion.find("(") == 0 && ecuacion.find_last_of(")") == ecuacion.length() - 1)
    {
        ecuacion.pop_back();
        ecuacion.erase(ecuacion.begin());
        if (ecuacion.find_first_of(")") < ecuacion.find_first_of("("))
        {
            ecuacion = ecuacion + ")";
            ecuacion = "(" + ecuacion;
        }
    }
    // Primero voy a buscar los '+' y '-' que separan terminos
    // Como segundo paso hago lo mismo con '*' y '/'
    for (int priority = 0; priority < OPERATOR_PRIORITY_LEVELS; priority++)
    {
        n_pos = 0;
        for (auto itr = ecuacion.begin(); itr != ecuacion.end(); ++itr)
        {
            n_pos++;
            if ((*itr) == '(')
                n_parentesis++;
            if ((*itr) == ')')
                n_parentesis--;
            if (((*itr) == operators[priority][0] or (*itr) == operators[priority][1]) && n_parentesis == 0)
            {
                // Encontre un separador de terminos de la ecuacion
                nodo->left = new eqNode;
                nodo->left->left = NULL;
                nodo->left->right = NULL;
                nodo->right = new eqNode;
                nodo->right->left = NULL;
                nodo->right->right = NULL;
                nodo->operation = *itr;
                nodo->equation = ecuacion;
                nodo->result = 0;
                // Esta en la cima del arbol de izquierda a derecha
                string T1 = ecuacion.substr(0, n_pos - 1);
                string T2 = ecuacion.substr(n_pos);
                //cout << "Ecuacion del Nodo @" << nodo << ": " << T1 << " " << *itr << " " << T2 << endl;
                Parse(T1, nodo->left); // Parseo el primer termino
                //cout << "Nodo left @" << nodo->left << ": " << nodo->equation << " " << nodo->operation << endl;
                Parse(T2, nodo->right); // Parseo el segundo termino
                //cout << "Nodo right @" << nodo->right << ": " << nodo->equation << " " << nodo->operation << endl;
                operator_found = true;
                break;
            }
            if (operator_found)
                break;
        }
    }
    if (!operator_found)
    {
        // NO hay operadores en la formula bajo analisis
        // Implica que estamos tratando con un numero o una variable aislada.
        nodo->operation = 0;
        nodo->result = 0;
        nodo->equation = ecuacion;
    }
}

void Formula::showFormula()
{
    cout << root->equation << endl;
}

void Formula::DisplayTree(eqNode *nodo)
{
    cout << "Formula Completa: " << nodo->equation << " || Operador principal: " << nodo->operation << endl;
    if (nodo->left != NULL)
        DisplayTree(nodo->left);
    if (nodo->right != NULL)
        DisplayTree(nodo->right);
}

void Formula::DisplayTree()
{
    cout << "Formula Completa: " << root->equation << " || Operador principal: " << root->operation << endl;
    if (root->left != NULL)
        DisplayTree(root->left);
    if (root->right != NULL)
        DisplayTree(root->right);
}

// Constructor
Formula::Formula(string ecuacion)
{
    root = new eqNode;
    root->left = NULL;
    root->right = NULL;
    Parse(ecuacion, root);
}

// Constructor
Formula::Formula()
{
    root = NULL;
}

void Formula::deleteFormula(eqNode *nodo)
{
    if (nodo != NULL)
    {
        deleteFormula(nodo->left);
        deleteFormula(nodo->right);
        delete nodo;
    }
}

void Formula::deleteFormula()
{
    deleteFormula(root);
}

// Destructor
Formula::~Formula()
{
    deleteFormula();
}