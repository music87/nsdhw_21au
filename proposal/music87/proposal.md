### Proposal for Call Option Pricer ###

---

#### Basic Information ####

Github repository: https://github.com/music87/nsd-project-option-pricer

#### Problem to Solve ####

Black Scholes model is the earliest, fundamental closed-form algorithm for pricing European call option. It makes some unrealistic assumptions such as stock price should follow geometric Brownian motion and the implied volatility should be constant. To tackle the limitation, stochastic volatility models like Variance Gamma, Heston, and Bates grow up. However, these models usually need lots of time to do the calibration i.e. for every option with n different strike prices, the bias (can be measured by mean square error) between option market price and option model price should be minimized that usually has to take another n steps to compute. 

<img src="proposal_image/calibration.png" alt="calibration"  />

Hence, Carr and Maden develop a fast Fourier transform (FFT) method for option pricing in 1999 which overall only takes nlog⁡n steps. If the close form of the characteristic function of the stock log price's risk-neutral density function is known, FFT method can give a more efficient way to compute the option price than those stochastic volatility models. This project's purpose is to implement the FFT option pricing method. Since most of the implementation only uses high-level language like python and Matlab, here I will use low-level language C++ to implement and optimize it. The program will finally bind to python for python users.

#### Perspective Users ####

Quant developer who needs to price a derivative.

Someone who is interested in the financial application of fast fourier transform.

#### System Architecture ####

<img src="proposal_image/system_architecture.png" alt="system_architecture"  />



1. get the characteristic function $\phi_T(x)$ of stock log price

   > eg. the characteristic function from Black Scholes model is 
   > 
   > <img src="proposal_image/characteristic_function_black_scholes.png" alt="characteristic_function_black_scholes"  />
   > 
   > eg. the characteristic function from Heston model is
   > 
   > ![characteristic_function_heston](proposal_image/characteristic_function_heston.png)
   > 
   > eg. the characteristic function from Bates model is
   > 
   > ![characteristic_function_bates](proposal_image/characteristic_function_bates.png)
   
2. Fourier transform modified call option price to get $\psi_T(x)$

   > <img src="proposal_image/Fourier_transform.png" alt="Fourier_transform"  />
   
3. price call option using FFT can be computed using the following formula

   > <img src="proposal_image/FFT_option_pricer.png" alt="FFT_option_pricer"  />
   
   

#### API Description ####

+ CharacteristicFunction - compute the output of characteristic function of different models including black_scholes, heston, and bates

+ FourierTransformer - transform characteristic function output using Fourier method

+ FFTOptionPricer - compute the call option price using the output of FourierTransformer

#### Engineering Infrastructure ####

+ Build system

  + make

  + make test

  + make clean

+ Testing Framework
  + Pytest for python

+ Version control
  + Git

#### Schedule ####

| Week                 | Goal                                                         |
| :------------------- | :----------------------------------------------------------- |
| Week 1 (11/1~11/7)   | Research fast fourier transform for option pricing method and its implementation example. |
| Week 2 (11/8~11/14)  | Implement characteristic function of asset price.            |
| Week 3 (11/15~11/21) | Implement fourier transformation of chatacteristic function. |
| Week 4 (11/22~11/28) | Implement FFT option pricer.                                 |
| Week 5 (11/29~12/5)  | Combine three components together.                           |
| Week 6 (12/6~12/12)  | Finish C++ implmentation part and wrap it to python by pybind11. |
| Week 7 (12/13~12/19) | Write some unit-tests to check the results and debug.        |
| Week 8 (12/20~12/26) | Write reports and prepare the presentation.                  |

#### Reference ####

+ [Matlab - optByHestonFFT](https://www.mathworks.com/help/fininst/optbyhestonfft.html#d123e191771)

+ [Python - fftoption](https://github.com/arraystream/fftoptionlib)

+ [Peter Carr, & Dilip B. Madan (1999). Option Valuation Using the Fast Fourier Transform. JOURNAL OF COMPUTATIONAL FINANCE, 2, 61–73.](https://engineering.nyu.edu/sites/default/files/2018-08/CarrMadan2_0.pdf) 

+ [Borak, Szymon & detlefsen, Kai & Härdle, Wolfgang Karl. (2005). FFT-based option pricing. 10.1007/3-540-27395-6_8.](https://www.econstor.eu/bitstream/10419/25030/1/496002368.PDF)

