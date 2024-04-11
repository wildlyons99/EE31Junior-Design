/* Authors: Chris Bann and Remy Ren
 * Library to check ambient light/light values based on a photoresistor.
 */

class Photoresistor {
    public:
        int readADC(int pinValue);
        double calculateVoltage(int adcValue, double refVoltage);
};