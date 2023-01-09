/********************************************************************************
* lin_reg.hpp: Innehåller funktionalitet för att enkelt kunna realisera
*              maskininlärningsmodeller baserade på linjär regression.
********************************************************************************/
#ifndef LIN_REG_HPP_
#define LIN_REG_HPP_

// Inkluderingsdirektiv:
#include <iostream>
#include <iomanip>
#include <vector>

/********************************************************************************
* lin_reg: Strukt för implementering av en enkel maskininlärningsmodell baserad 
*          på linjär regression. Träningsdata passeras via referenser till 
*          vektorer innehållande träningsuppsättningarnas in- och utsignaler. 
*          Träning genomförs under godtyckligt antal epoker med godtycklig
*          lärhastighet.
********************************************************************************/
struct lin_reg
{
   std::vector<double> train_in;         // Träningsuppsättningarnas insignaler. 
   std::vector<double> train_out;        // Träningsuppsättningarnas utsignaler. 
   std::vector<std::size_t> train_order; // Ordningsföljd för träningsuppsättningar. 
   double bias = 0.0;                    // Vilovärde (m-värde). 
   double weight = 0.0;                  // Vikt (k-värde). 

   /********************************************************************************
   * num_training_sets: Returnerar antalet befintliga träningsuppsättningar.
   ********************************************************************************/
   std::size_t num_training_sets(void) const
   { 
      return this->train_order.size();
   }

   /********************************************************************************
   * check_training_data_size: Kontrollerar att antalet träningsuppsättningar är
   *                           jämfört fördelat mellan in- och utdata. Om detta
   *                           inte är fallet justeras antalet uppsättningar.
   ********************************************************************************/
   void check_training_data_size(void)
   {
      if (this->train_in.size() != this->train_out.size())
      {
         const auto num_sets = this->train_in.size() <= this->train_out.size() ?
            this->train_in.size() : this->train_out.size();

         this->train_in.resize(num_sets);
         this->train_out.resize(num_sets);
      }
      return;
   }

   /********************************************************************************
   * init_training_order: Initierar vektor som lagrar index för den inbördes
   *                      ordningsföljden för träningsuppsättningarna vid träning.
   *                      Först sker kontroll att antalet träningsuppsättningar
   *                      är jämt fördelat mellan in- och utdata.
   ********************************************************************************/
   void init_training_order(void)
   {
      this->check_training_data_size();
      this->train_order.resize(this->train_in.size());

      for (std::size_t i = 0; i < this->num_training_sets(); ++i)
      {
         this->train_order[i] = i;
      }
      return;
   }
   
   /********************************************************************************
   * set_training_data: Läser in träningsdata för angiven regressionsmodell via
   *                    passerade in- och utsignaler, tillsammans med index för
   *                    respektive träningsuppsättning.
 
   *                    - train_in : Innehåller träningsuppsättningarnas insignaler.
   *                    - train_out: Innehåller träningsuppsättningarnas utsignaler.
   ********************************************************************************/
   void set_training_data(const std::vector<double>& train_in,
                          const std::vector<double>& train_out)
   {
      this->train_in = train_in;
      this->train_out = train_out;
      this->init_training_order();
      return;
   }

   /********************************************************************************
   * train: Tränar angiven regressionsmodell med befintlig träningsdata under
   *        angivet antal epoker samt lärhastighet. I början av varje ny epok
   *        randomiseras ordningen på träningsuppsättningarna för att undvika att
   *        eventuella icke avsedda mönster i träningsdatan påverkar resultatet.
   *
   *        För varje träningsuppsättning sker en prediktion via aktuell insignal.
   *        Det predikterade värdet jämförs mot referensvärdet erhållet från
   *        träningsdatan. Aktuellt fel beräknas som differensen mellan
   *        referensvärdet samt det predikterade värdet. En bråkdel av felet
   *        används för att justera modellens parametrar i syfte att minska felet.
   *
   *        - num_epochs   : Antalet epoker/omgångar som träning skall genomföras.
   *        - learning_rate: Lärhastighet, avgör hur stor andel av aktuellt fel
   *                         som modellens parametrar justeras med.
   ********************************************************************************/
   void train(const std::size_t num_epochs,
              const double learning_rate)
   {
      return;
   }

   /********************************************************************************
  * predict: Genomför prediktion med angiven indata och returnerar resultatet.
  * 
  *          - input: Indata som prediktion ska genomföras med.
  ********************************************************************************/
   double predict(const double input) const
   { 
      return this->weight * input + this->bias; 
   }

   /********************************************************************************
   * predict_range: Genomför prediktion med angiven regressionsmodell för
   *                datapunkter inom intervallet mellan angivet min- och maxvärde
   *                [min, max] med angiven stegringshastighet step, som sätts till
   *                1.0 som default.
   *
   *                Varje insignal skrivs ut tillsammans med motsvarande predikterat
   *                värde via angiven utström, där standardutenheten std::cout
   *                används som default för utskrift i terminalen.
   *
   *                - min         : Lägsta värde för datatpunkter som skall testas.
   *                - max         : Högsta värde för datatpunkter som skall testas.
   *                - step        : Stegringshastigheten, dvs. differensen mellan
   *                                varje datapunkt som testas (default = 1.0).
                    - ostream     : Referens till utström (default = std::cout).
                    - num_decimals: Antalet decimaler som skrivs ut per flyttal.
   ********************************************************************************/
   void predict_range(const double min,
                      const double max,
                      const double step = 1.0,
                      std::ostream& ostream = std::cout,
                      const int num_decimals = 1)
   {
      std::fixed(ostream);

      if (min >= max)
      {
         std::cerr << "Error: Minimum input value cannot be higher or equal to maximum input value!\n\n";
         return;
      }

      ostream << "--------------------------------------------------------------------------------\n";

      for (auto i = min; i <= max; i = i + step)
      {
         const auto prediction = this->weight * i + this->bias;

         ostream << std::setprecision(num_decimals) << "Input: " << i << "\n";
         ostream << std::setprecision(num_decimals) << "Predicted output: " << prediction << "\n";

         if (i < max) ostream << "\n";
      }

      ostream << "--------------------------------------------------------------------------------\n\n";
      return;
   }

   /********************************************************************************
   * predict_all: Genomför prediktion med angiven regressionsmodell via insignaler
   *              från samtliga befintliga träningsuppsättninsuppsättningar och
   *              skriver ut varje insignal samt motsvarande predikterat värde via
   *              angiven utström, där standardutenheten std::cout används som
   *              default för utskrift i terminalen.
   *
   *              - ostream     : Referens till utström (default = std::cout).
   *              - num_decimals: Antalet decimaler som skrivs ut per flyttal.
   ********************************************************************************/
   void predict_all(std::ostream& ostream = std::cout,
                    const int num_decimals = 1)
   {
      std::fixed(ostream);

      if (this->num_training_sets() == 0)
      {
         std::cerr << "Training data missing!\n\n";
         return;
      }

      const auto* end = &this->train_in[this->train_in.size() - 1];
      ostream << "--------------------------------------------------------------------------------\n";

      for (auto& i : this->train_in)
      {
         const auto prediction = this->weight * i + this->bias;

         ostream << std::setprecision(num_decimals) << "Input:\t" << i << "\n";
         ostream << std::setprecision(num_decimals) << "Predicted output:\t" << prediction << "\n";

         if (&i < end) ostream << "\n";
      }

      ostream << "--------------------------------------------------------------------------------\n\n";
      return;
   }

   /********************************************************************************
   * shuffle: Randomiserar den inbördes ordningen på träningsuppsättningarna för
   *          angiven regressionsmodell. Detta genomförs i syfte att minska risken
   *          att eventuella icke avsedda mönster som förekommer i träningsdatan
   *          skall påverkar träningen av regressionsmodellen.
   ********************************************************************************/
   void shuffle(void)
   {
      for (std::size_t i = 0; i < this->num_training_sets(); ++i)
      {
      }

      return;
   }

   /********************************************************************************
   * optimize: Beräknar aktuellt fel och justerar angiven regressionsmodells
   *           parametrar utefter detta.
   *
   *           input        : Insignal som prediktion skall genomföras med.
   *           reference    : Referensvärde från träningsdatan, vilket utgör det
   *                          värde som modellen önskas prediktera.
   *           learning_rate: Modellens lärhastighet, avgör hur mycket modellens
   *                          parametrar justeras vid fel.
   ********************************************************************************/
   void optimize(const double input,
                 const double reference,
                 const double learning_rate)
   {
      return;
   }
};

#endif /* LIN_REG_HPP_ */