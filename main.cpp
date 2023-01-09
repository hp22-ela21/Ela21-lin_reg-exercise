/********************************************************************************
* main.cpp: Implementering av en enkel modell som baseras på linjär regression.
*           Slutför medlemsfunktioner i strukten lin_reg så att modellen 
*           predikterar i enlighet med formeln y = 10x + 2.
********************************************************************************/
#include "lin_reg.hpp"

/********************************************************************************
* main: Tränar en modell baserad på linjär regression via träningsdata bestående
*       av fem träningsuppsättningar, lagrade via var sin vektor. Modellen
*       tränas under 10 000 epoker med en lärhastighet på 1 %.
*
*       Efter träningen är slutförd sker prediktion för samtliga insignaler
*       mellan -10 och 10 med en stegringshastighet på 1.0. Varje insignal
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