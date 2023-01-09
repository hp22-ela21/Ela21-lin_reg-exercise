/********************************************************************************
* main.cpp: Implementering av en enkel modell som baseras p� linj�r regression,
*           med tr�ningsdata deklarerat direkt i funktionen main och lagrat via
*           tv� vektorer. Tr�ningsdatan kan �ndras hur som helst vid behov, men
*           antalet in- och utsignaler m�ste vara samma f�r lyckad tr�ning.
********************************************************************************/
#include "lin_reg.hpp"

/********************************************************************************
* main: Tr�nar en modell baserad p� linj�r regression via tr�ningsdata best�ende
*       av fem tr�ningsupps�ttningar, lagrade via var sin vektor. Modellen
*       tr�nas under 10 000 epoker med en l�rhastighet p� 1 %.
*
*       Efter tr�ningen �r slutf�rd sker prediktion f�r samtliga insignaler
*       mellan -10 och 10 med en stegringshastighet p� 1.0. Varje insignal
*       i detta intervall skrivs ut i terminalen tillsammans med predikterad
*       utsignal.
********************************************************************************/
int main(void)
{
   const std::vector<double> train_in = { 0, 1, 2, 3, 4 };
   const std::vector<double> train_out = { 2, 12, 22, 32, 42 };

   lin_reg l1;
   l1.set_training_data(train_in, train_out);
   l1.train(10000, 0.01);
   l1.predict_range(-10, 10);
   return 0;
}