for (( i=1; i<=100; i++ ))
do

  if [ -e crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_0_*.root ];then
     mv crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_0_*.root crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_1.root
     echo -n "Renaming: "; echo -n $i; echo "_1.root"
  fi

  if [ -e crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_1_*.root ];then
     mv crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_1_*.root crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_1.root
     echo -n "Renaming: "; echo -n $i; echo "_1.root"
  fi

  if [ -e crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_2_*.root ];then
     mv crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_2_*.root crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_1.root
     echo -n "Renaming: "; echo -n $i; echo "_1.root"
  fi

  if [ -e crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_3_*.root ];then
     mv crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_3_*.root crab_0_101110_020407/res/test_sim_redigirereco_noassoc_AMPT_`expr $i`_1.root
     echo -n "Renaming: "; echo -n $i; echo "_1.root"
  fi
done
