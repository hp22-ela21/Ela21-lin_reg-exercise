/********************************************************************************
* lin_reg.hpp: Inneh�ller funktionalitet f�r att enkelt kunna realisera
*              maskininl�rningsmodeller baserade p� linj�r regression.
********************************************************************************/
#ifndef LIN_REG_HPP_
#define LIN_REG_HPP_

// Inkluderingsdirektiv:
#include <iostream>
#include <iomanip>
#include <vector>

/********************************************************************************
* lin_reg: Strukt f�r implementering av en enkel maskininl�rningsmodell baserad 
*          p� linj�r regression. Tr�ningsdata passeras via referenser till 
*          vektorer inneh�llande tr�ningsupps�ttningarnas in- och utsignaler. 
*          Tr�ning genomf�rs under godtyckligt antal epoker med godtycklig
*          l�rhastighet.
********************************************************************************/
struct lin_reg
{
   std::vector<double> train_in;         // Tr�ningsupps�ttningarnas insignaler. 
   std::vector<double> train_out;        // Tr�ningsupps�ttningarnas utsignaler. 
   std::vector<std::size_t> train_order; // Ordningsf�ljd f�r tr�ningsupps�ttningar. 
   double bias = 0.0;                    // Vilov�rde (m-v�rde). 
   double weight = 0.0;                  // Vikt (k-v�rde). 

   /********************************************************************************
   * num_training_sets: Returnerar antalet befintliga tr�ningsupps�ttningar.
   ********************************************************************************/
   std::size_t num_training_sets(void) const
   { 
      return this->train_order.size();
   }

   /********************************************************************************
   * check_training_data_size: Kontrollerar att antalet tr�ningsupps�ttningar �r
   *                           j�mf�rt f�rdelat mellan in- och utdata. Om detta
   *                           inte �r fallet justeras antalet upps�ttningar.
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
   * init_training_order: Initierar vektor som lagrar index f�r den inb�rdes
   *                      ordningsf�ljden f�r tr�ningsupps�ttningarna vid tr�ning.
   *                      F�rst sker kontroll att antalet tr�ningsupps�ttningar
   *                      �r j�mt f�rdelat mellan in- och utdata.
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
   * set_training_data: L�ser in tr�ningsdata f�r angiven regressionsmodell via
   *                    passerade in- och utsignaler, tillsammans med index f�r
   *                    respektive tr�ningsupps�ttning.
 
   *                    - train_in : Inneh�ller tr�ningsupps�ttningarnas insignaler.
   *                    - train_out: Inneh�ller tr�ningsupps�ttningarnas utsignaler.
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
   * train: Tr�nar angiven regressionsmodell med befintlig tr�ningsdata under
   *        angivet antal epoker samt l�rhastighet. I b�rjan av varje ny epok
   *        randomiseras ordningen p� tr�ningsupps�ttningarna f�r att undvika att
   *        eventuella icke avsedda m�nster i tr�ningsdatan p�verkar resultatet.
   *
   *        F�r varje tr�ningsupps�ttning sker en prediktion via aktuell insignal.
   *        Det predikterade v�rdet j�mf�rs mot referensv�rdet erh�llet fr�n
   *        tr�ningsdatan. Aktuellt fel ber�knas som differensen mellan
   *        referensv�rdet samt det predikterade v�rdet. En br�kdel av felet
   *        anv�nds f�r att justera modellens parametrar i syfte att minska felet.
   *
   *        - num_epochs   : Antalet epoker/omg�ngar som tr�ning skall genomf�ras.
   *        - learning_rate: L�rhastighet, avg�r hur stor andel av aktuellt fel
   *                         som modellens parametrar justeras med.
   ********************************************************************************/
   void train(const std::size_t num_epochs,
              const double learning_rate)
   {
      return;
   }

   /********************************************************************************
  * predict: Genomf�r prediktion med angiven indata och returnerar resultatet.
  * 
  *          - input: Indata som prediktion ska genomf�ras med.
  ********************************************************************************/
   double predict(const double input) const
   { 
      return this->weight * input + this->bias; 
   }

   /********************************************************************************
   * predict_range: Genomf�r prediktion med angiven regressionsmodell f�r
   *                datapunkter inom intervallet mellan angivet min- och maxv�rde
   *                [min, max] med angiven stegringshastighet step, som s�tts till
   *                1.0 som default.
   *
   *                Varje insignal skrivs ut tillsammans med motsvarande predikterat
   *                v�rde via angiven utstr�m, d�r standardutenheten std::cout
   *                anv�nds som default f�r utskrift i terminalen.
   *
   *                - min         : L�gsta v�rde f�r datatpunkter som skall testas.
   *                - max         : H�gsta v�rde f�r datatpunkter som skall testas.
   *                - step        : Stegringshastigheten, dvs. differensen mellan
   *                                varje datapunkt som testas (default = 1.0).
                    - ostream     : Referens till utstr�m (default = std::cout).
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
   * predict_all: Genomf�r prediktion med angiven regressionsmodell via insignaler
   *              fr�n samtliga befintliga tr�ningsupps�ttninsupps�ttningar och
   *              skriver ut varje insignal samt motsvarande predikterat v�rde via
   *              angiven utstr�m, d�r standardutenheten std::cout anv�nds som
   *              default f�r utskrift i terminalen.
   *
   *              - ostream     : Referens till utstr�m (default = std::cout).
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
   * shuffle: Randomiserar den inb�rdes ordningen p� tr�ningsupps�ttningarna f�r
   *          angiven regressionsmodell. Detta genomf�rs i syfte att minska risken
   *          att eventuella icke avsedda m�nster som f�rekommer i tr�ningsdatan
   *          skall p�verkar tr�ningen av regressionsmodellen.
   ********************************************************************************/
   void shuffle(void)
   {
      for (std::size_t i = 0; i < this->num_training_sets(); ++i)
      {
      }

      return;
   }

   /********************************************************************************
   * optimize: Ber�knar aktuellt fel och justerar angiven regressionsmodells
   *           parametrar utefter detta.
   *
   *           input        : Insignal som prediktion skall genomf�ras med.
   *           reference    : Referensv�rde fr�n tr�ningsdatan, vilket utg�r det
   *                          v�rde som modellen �nskas prediktera.
   *           learning_rate: Modellens l�rhastighet, avg�r hur mycket modellens
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