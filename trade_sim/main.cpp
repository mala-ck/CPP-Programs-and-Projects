/* Program for trading simulaiton
• Starting capital is $5,000.!
• Invest 15% of capital on hand per trade.!
• Expected return is 20% of the capital invested per trade.!
• Each trade lasts 4 weeks. The original capital plus the return gained is put back into
the capital on hand.!
• A new trade is executed every two weeks.!
• 10 total trades.!
 */

#include <iostream>
#include <cmath>

using namespace std;

#define NUM_TRADES 10
#define TRADE_WINDOW_WEEKS 4
#define TRADE_FREQUENCY_WEEKS 2
#define ORIGINAL_CAP 5000

int main()
{
    //cout << "Hello World!" << endl;
    float arr_cap_on_hand[NUM_TRADES];
    arr_cap_on_hand[0] = ORIGINAL_CAP;

    float arr_trade_inv[NUM_TRADES];

    //10 trades occur with each trade every 2 weeks
    for(int trade_cnt = 0; trade_cnt<10; trade_cnt++)
    {
        if( trade_cnt > 0) // Calculate capital on hand
        {
            arr_cap_on_hand[trade_cnt] = arr_cap_on_hand[trade_cnt-1] - arr_trade_inv[trade_cnt-1] ;
        }

        if(trade_cnt > 1 ) // This means it is returns week too. So add returns before trading
        {
            float returns = arr_trade_inv[trade_cnt - 2]*1.2 ;
            arr_cap_on_hand[trade_cnt] = arr_cap_on_hand[trade_cnt] + returns ;
            cout << " Returns " << trade_cnt -2 << " : " << returns;
            cout << endl;
        }

        cout<< " Cap on hand " << trade_cnt << " : " << arr_cap_on_hand[trade_cnt];

        //Calculate invetment
        arr_trade_inv[trade_cnt] = 0.15 * arr_cap_on_hand[trade_cnt];

        cout << " Trade inv " << trade_cnt << " : " << arr_trade_inv[trade_cnt];

        cout << endl;
    }

float final_total = arr_cap_on_hand[NUM_TRADES -1] + arr_trade_inv[NUM_TRADES-1]*1.2;

cout << " Final amount : " <<  final_total;

    return 0;
}

