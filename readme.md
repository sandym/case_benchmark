
# Result on M1 cpu:


```
benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
tolower - for_each                             100             1    105.772 ms 
                                        1.05824 ms    1.05651 ms    1.06015 ms 
                                        9.33237 us    8.50413 us    10.7832 us 
                                                                               
tolower - for loop with if                     100             1    45.3127 ms 
                                        453.158 us    452.877 us    453.777 us 
                                        2.01596 us    935.165 ns    3.40305 us 
                                                                               
tolower - absl table                           100             1    26.6362 ms 
                                        265.299 us    265.233 us     265.42 us 
                                        441.054 ns    265.839 ns    666.564 ns 
                                                                               
tolower - vec8                                 100             1    17.3376 ms 
                                        173.517 us    173.318 us    173.989 us 
                                        1.47257 us    749.133 ns     2.8742 us 
                                                                               

===============================================================================
All tests passed (5 assertions in 1 test case)
```
