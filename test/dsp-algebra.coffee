require '../lib/test-tools'

describe "DSP", ->
  describe ".add", ->
    it "should provide correct results", ->
      dst = F(4)
      DSP.add(dst, F([520,933,26,933]), F([813,80,395,524]))
      dst.should.be.identicalTo([1333,1013,421,1457])

      dst = F(4)
      DSP.add(dst, F([673,51,891,553]), F([205,397,533,839]))
      dst.should.be.identicalTo([878,448,1424,1392])

      dst = F(4)
      DSP.add(dst, F([873,980,130,131]), F([870,118,578,731]))
      dst.should.be.identicalTo([1743,1098,708,862])

      dst = F(4)
      DSP.add(dst, F([894,800,258,21]), F([800,50,749,438]))
      dst.should.be.identicalTo([1694,850,1007,459])

      dst = F(4)
      DSP.add(dst, F([203,377,512,864]), F([351,31,162,364]))
      dst.should.be.identicalTo([554,408,674,1228])

      dst = F(4)
      DSP.add(dst, F([132,56,913,967]), F([243,363,70,685]))
      dst.should.be.identicalTo([375,419,983,1652])

      dst = F(4)
      DSP.add(dst, F([686,145,296,938]), F([975,487,680,654]))
      dst.should.be.identicalTo([1661,632,976,1592])

      dst = F(4)
      DSP.add(dst, F([892,657,716,186]), F([722,76,698,287]))
      dst.should.be.identicalTo([1614,733,1414,473])

      dst = F(4)
      DSP.add(dst, F([610,949,652,176]), F([970,432,853,546]))
      dst.should.be.identicalTo([1580,1381,1505,722])

    it "should be able to deal with negative values", ->
      dst = F(4)
      DSP.add(dst, F([355,565,422,845]), F([-702,-22,-623,-647]))
      dst.should.be.identicalTo([-347,543,-201,198])

      dst = F(4)
      DSP.add(dst, F([428,313,53,364]), F([-535,-777,-884,-273]))
      dst.should.be.identicalTo([-107,-464,-831,91])

      dst = F(4)
      DSP.add(dst, F([727,281,303,862]), F([-849,-698,-303,-396]))
      dst.should.be.identicalTo([-122,-417,0,466])

      dst = F(4)
      DSP.add(dst, F([920,3,667,323]), F([-344,-748,-216,-266]))
      dst.should.be.identicalTo([576,-745,451,57])

      dst = F(4)
      DSP.add(dst, F([947,322,704,844]), F([-972,-812,-325,-50]))
      dst.should.be.identicalTo([-25,-490,379,794])

      dst = F(4)
      DSP.add(dst, F([193,957,541,94]), F([-64,-280,-450,-812]))
      dst.should.be.identicalTo([129,677,91,-718])

      dst = F(4)
      DSP.add(dst, F([29,174,265,221]), F([-814,-215,-744,-707]))
      dst.should.be.identicalTo([-785,-41,-479,-486])

      dst = F(4)
      DSP.add(dst, F([944,812,564,771]), F([-382,-37,-10,-419]))
      dst.should.be.identicalTo([562,775,554,352])

      dst = F(4)
      DSP.add(dst, F([463,210,619,713]), F([-358,-396,-403,-927]))
      dst.should.be.identicalTo([105,-186,216,-214])

    it "should be able to deal with decimal values", ->
      dst = F(4)
      DSP.add(dst, F([928.2731204293668,170.75876030139625,228.07836788706481,651.8935258500278]), F([558.4024842828512,191.80249935016036,-307.2676961310208,-377.12726881727576]))
      dst.should.be.identicalTo([1486.675604712218,362.5612596515566,-79.18932824395597,274.76625703275204])

      dst = F(4)
      DSP.add(dst, F([432.289281161502,777.1773508284241,357.33340634033084,348.4100478235632]), F([214.60453560575843,15.361420344561338,302.01931530609727,-47.50380478799343]))
      dst.should.be.identicalTo([646.8938167672604,792.5387711729854,659.3527216464281,300.9062430355698])

      dst = F(4)
      DSP.add(dst, F([536.0136260278523,808.5912100505084,717.789703514427,902.4504721164703]), F([767.3521446995437,-757.4979136697948,609.7105238586664,835.2493201382458]))
      dst.should.be.identicalTo([1303.365770727396,51.09329638071358,1327.5002273730934,1737.6997922547162])

      dst = F(4)
      DSP.add(dst, F([616.5154003538191,518.363538198173,690.8418701495975,627.7299106586725]), F([-915.8251844346523,924.1671226918697,-370.4560659825802,-503.6317980848253]))
      dst.should.be.identicalTo([-299.3097840808332,1442.5306608900428,320.38580416701734,124.09811257384717])

      dst = F(4)
      DSP.add(dst, F([460.6678148265928,441.6358263697475,971.0737862624228,886.6275728214532]), F([300.86274119094014,-329.71318904310465,-775.3827702254057,-59.54971443861723]))
      dst.should.be.identicalTo([761.530556017533,111.92263732664287,195.6910160370171,827.077858382836])

      dst = F(4)
      DSP.add(dst, F([156.55781188979745,724.4394454173744,915.1654120068997,121.68041779659688]), F([-782.7154528349638,961.9570001959801,501.00817857310176,276.47999906912446]))
      dst.should.be.identicalTo([-626.1576409451663,1686.3964456133544,1416.1735905800015,398.16041686572134])

      dst = F(4)
      DSP.add(dst, F([726.007352117449,698.6253033392131,373.70377918705344,201.5428093727678]), F([61.675094068050385,-857.4118274264038,-907.3779773898423,245.91980362311006]))
      dst.should.be.identicalTo([787.6824461854994,-158.78652408719063,-533.6741982027888,447.46261299587786])

      dst = F(4)
      DSP.add(dst, F([869.3540701642632,506.5015603322536,812.2525953222066,184.90066984668374]), F([191.43883604556322,-306.3516952097416,-811.2696930766106,-125.47460803762078]))
      dst.should.be.identicalTo([1060.7929062098265,200.14986512251198,0.9829022455960512,59.42606180906296])

      dst = F(4)
      DSP.add(dst, F([195.02501864917576,654.271325096488,33.24427921324968,972.8467755485326]), F([766.1943477578461,-793.5745692811906,27.450398541986942,-35.36770353093743]))
      dst.should.be.identicalTo([961.2193664070219,-139.30324418470263,60.694677755236626,937.4790720175952])

  describe ".sub", ->
    it "should provide correct results", ->
      dst = F(4)
      DSP.sub(dst, F([748,874,314,105]), F([359,722,223,191]))
      dst.should.be.identicalTo([389,152,91,-86])

      dst = F(4)
      DSP.sub(dst, F([17,847,171,862]), F([162,350,599,854]))
      dst.should.be.identicalTo([-145,497,-428,8])

      dst = F(4)
      DSP.sub(dst, F([62,912,523,482]), F([614,59,64,752]))
      dst.should.be.identicalTo([-552,853,459,-270])

      dst = F(4)
      DSP.sub(dst, F([565,251,251,995]), F([603,194,277,623]))
      dst.should.be.identicalTo([-38,57,-26,372])

      dst = F(4)
      DSP.sub(dst, F([255,901,513,782]), F([317,376,926,236]))
      dst.should.be.identicalTo([-62,525,-413,546])

      dst = F(4)
      DSP.sub(dst, F([872,766,300,978]), F([260,310,341,812]))
      dst.should.be.identicalTo([612,456,-41,166])

      dst = F(4)
      DSP.sub(dst, F([326,997,619,265]), F([559,814,776,359]))
      dst.should.be.identicalTo([-233,183,-157,-94])

      dst = F(4)
      DSP.sub(dst, F([437,713,25,341]), F([136,496,212,516]))
      dst.should.be.identicalTo([301,217,-187,-175])

      dst = F(4)
      DSP.sub(dst, F([330,561,235,741]), F([646,599,281,142]))
      dst.should.be.identicalTo([-316,-38,-46,599])

    it "should be able to deal with negative values", ->
      dst = F(4)
      DSP.sub(dst, F([327,183,417,75]), F([-687,-185,-228,-810]))
      dst.should.be.identicalTo([1014,368,645,885])

      dst = F(4)
      DSP.sub(dst, F([65,716,480,391]), F([-732,-160,-95,-355]))
      dst.should.be.identicalTo([797,876,575,746])

      dst = F(4)
      DSP.sub(dst, F([290,175,692,580]), F([-526,-31,-49,-373]))
      dst.should.be.identicalTo([816,206,741,953])

      dst = F(4)
      DSP.sub(dst, F([449,327,153,635]), F([-912,-995,-763,-261]))
      dst.should.be.identicalTo([1361,1322,916,896])

      dst = F(4)
      DSP.sub(dst, F([868,482,405,706]), F([-695,-474,-212,-579]))
      dst.should.be.identicalTo([1563,956,617,1285])

      dst = F(4)
      DSP.sub(dst, F([400,526,166,144]), F([-516,-662,-997,-219]))
      dst.should.be.identicalTo([916,1188,1163,363])

      dst = F(4)
      DSP.sub(dst, F([455,629,22,373]), F([-496,-70,-98,-644]))
      dst.should.be.identicalTo([951,699,120,1017])

      dst = F(4)
      DSP.sub(dst, F([404,957,117,425]), F([-300,-11,-19,-133]))
      dst.should.be.identicalTo([704,968,136,558])

      dst = F(4)
      DSP.sub(dst, F([866,555,862,199]), F([-808,-552,-438,-649]))
      dst.should.be.identicalTo([1674,1107,1300,848])

    it "should be able to deal with decimal values", ->
      dst = F(4)
      DSP.sub(dst, F([809.8935454618186,575.286474544555,663.9257813803852,380.0766367930919]), F([-216.6361277922988,831.4814930781722,-169.8223827406764,-274.6396795846522]))
      dst.should.be.identicalTo([1026.5296732541174,-256.19501853361726,833.7481641210616,654.7163163777441])

      dst = F(4)
      DSP.sub(dst, F([393.4298262465745,557.4273471720517,626.8228059634566,833.1290339119732]), F([-119.25806850194931,-577.323033940047,-170.12919392436743,-522.7245017886162]))
      dst.should.be.identicalTo([512.6878947485238,1134.7503811120987,796.9519998878241,1355.8535357005894])

      dst = F(4)
      DSP.sub(dst, F([735.7853350695223,616.2270060740411,727.6411228813231,969.0207373350859]), F([207.997371442616,-926.9305975176394,811.9026650674641,40.57097854092717]))
      dst.should.be.identicalTo([527.7879636269063,1543.1576035916805,-84.26154218614101,928.4497587941587])

      dst = F(4)
      DSP.sub(dst, F([903.367244405672,627.7147461660206,728.6925693042576,838.4448331780732]), F([-558.6629654280841,356.3763122074306,-618.723657913506,119.20603783801198]))
      dst.should.be.identicalTo([1462.030209833756,271.33843395859003,1347.4162272177637,719.2387953400612])

      dst = F(4)
      DSP.sub(dst, F([860.3362827561796,216.03487734682858,130.9215477667749,159.81538547202945]), F([-216.04138566181064,467.51132933422923,847.9889836162329,-243.4744075872004]))
      dst.should.be.identicalTo([1076.3776684179902,-251.47645198740065,-717.067435849458,403.28979305922985])

      dst = F(4)
      DSP.sub(dst, F([772.1048153471202,772.7494311984628,826.3819334097207,101.47757176309824]), F([-460.66329069435596,-226.60646447911859,-974.9424336478114,-907.3265506885946]))
      dst.should.be.identicalTo([1232.7681060414761,999.3558956775814,1801.324367057532,1008.8041224516928])

      dst = F(4)
      DSP.sub(dst, F([164.17661821469665,809.0546200983226,745.565984165296,989.3110485281795]), F([725.9379322640598,702.4093791842461,546.1120223626494,-756.1180992051959]))
      dst.should.be.identicalTo([-561.7613140493631,106.64524091407657,199.45396180264652,1745.4291477333754])

      dst = F(4)
      DSP.sub(dst, F([87.87339041009545,944.1272504627705,663.943590130657,831.4637050498277]), F([281.42958506941795,-558.0383040942252,653.7407203577459,-841.7265336029232]))
      dst.should.be.identicalTo([-193.5561946593225,1502.1655545569956,10.202869772911072,1673.1902386527508])

      dst = F(4)
      DSP.sub(dst, F([792.8579342551529,192.69335665740073,720.7607855089009,240.7623529434204]), F([-590.1610287837684,391.24993048608303,763.7472273781896,-257.1048908866942]))
      dst.should.be.identicalTo([1383.0189630389214,-198.5565738286823,-42.98644186928868,497.8672438301146])

  describe ".mul", ->
    it "should provide correct results", ->
      dst = F(4)
      DSP.mul(dst, F([126,234,144,382]), F([789,895,500,711]))
      dst.should.be.identicalTo([99414,209430,72000,271602])

      dst = F(4)
      DSP.mul(dst, F([847,75,899,843]), F([722,766,878,222]))
      dst.should.be.identicalTo([611534,57450,789322,187146])

      dst = F(4)
      DSP.mul(dst, F([354,801,319,823]), F([738,919,917,139]))
      dst.should.be.identicalTo([261252,736119,292523,114397])

      dst = F(4)
      DSP.mul(dst, F([341,826,865,782]), F([327,102,618,658]))
      dst.should.be.identicalTo([111507,84252,534570,514556])

      dst = F(4)
      DSP.mul(dst, F([339,619,655,875]), F([40,184,123,98]))
      dst.should.be.identicalTo([13560,113896,80565,85750])

      dst = F(4)
      DSP.mul(dst, F([828,667,164,371]), F([770,773,124,782]))
      dst.should.be.identicalTo([637560,515591,20336,290122])

      dst = F(4)
      DSP.mul(dst, F([905,880,794,834]), F([297,265,842,982]))
      dst.should.be.identicalTo([268785,233200,668548,818988])

      dst = F(4)
      DSP.mul(dst, F([700,389,648,630]), F([385,820,207,113]))
      dst.should.be.identicalTo([269500,318980,134136,71190])

      dst = F(4)
      DSP.mul(dst, F([528,461,21,439]), F([842,120,474,703]))
      dst.should.be.identicalTo([444576,55320,9954,308617])

    it "should be able to deal with negative values", ->
      dst = F(4)
      DSP.mul(dst, F([687,911,931,614]), F([-401,-709,-555,-727]))
      dst.should.be.identicalTo([-275487,-645899,-516705,-446378])

      dst = F(4)
      DSP.mul(dst, F([59,537,810,150]), F([-102,-929,-69,-810]))
      dst.should.be.identicalTo([-6018,-498873,-55890,-121500])

      dst = F(4)
      DSP.mul(dst, F([994,320,491,425]), F([-303,-619,-473,-30]))
      dst.should.be.identicalTo([-301182,-198080,-232243,-12750])

      dst = F(4)
      DSP.mul(dst, F([596,271,919,116]), F([-278,-764,-557,-346]))
      dst.should.be.identicalTo([-165688,-207044,-511883,-40136])

      dst = F(4)
      DSP.mul(dst, F([710,458,213,361]), F([-968,-32,-443,-186]))
      dst.should.be.identicalTo([-687280,-14656,-94359,-67146])

      dst = F(4)
      DSP.mul(dst, F([590,647,817,463]), F([-150,-930,-900,-732]))
      dst.should.be.identicalTo([-88500,-601710,-735300,-338916])

      dst = F(4)
      DSP.mul(dst, F([656,692,578,191]), F([-722,-479,-840,-732]))
      dst.should.be.identicalTo([-473632,-331468,-485520,-139812])

      dst = F(4)
      DSP.mul(dst, F([600,124,233,715]), F([-612,-134,-554,-189]))
      dst.should.be.identicalTo([-367200,-16616,-129082,-135135])

      dst = F(4)
      DSP.mul(dst, F([272,309,890,418]), F([-515,-535,-264,-288]))
      dst.should.be.identicalTo([-140080,-165315,-234960,-120384])

    it "should be able to deal with decimal values", ->
      dst = F(4)
      DSP.mul(dst, F([931.9279678165913,406.16391226649284,115.81271444447339,968.071170616895]), F([-289.039742667228,188.41300252825022,-163.57188019901514,469.7651811875403]))
      dst.should.be.identicalTo([-269364.2200021003,76526.56222875071,-18943.703452634152,454766.1288672799])

      dst = F(4)
      DSP.mul(dst, F([6.601742468774319,959.7415192984045,435.6935820542276,996.2845942936838]), F([-135.38007391616702,657.4707361869514,890.8650679513812,-743.7099302187562]))
      dst.should.be.identicalTo([-893.7443833981662,631001.9632423052,388144.19258272013,-740946.7461001774])

      dst = F(4)
      DSP.mul(dst, F([477.8260258026421,457.61712081730366,671.1496580392122,346.23845014721155]), F([-656.8455821834505,-567.8418725728989,690.092577598989,568.6910478398204]))
      dst.should.be.identicalTo([-313857.91410074086,-259854.16280631622,463155.39747096,196902.70701665315])

      dst = F(4)
      DSP.mul(dst, F([961.9660442695022,663.7635626830161,396.71542355790734,239.97521121054888]), F([-47.41718899458647,352.2200803272426,938.3455640636384,871.0488262586296]))
      dst.should.be.identicalTo([-45613.72572750172,233790.85536650865,372256.1578911898,209030.12605611532])

      dst = F(4)
      DSP.mul(dst, F([792.4383254721761,624.4225630071014,914.1855800990015,691.4137382991612]), F([-333.20268290117383,-742.6609667018056,992.5357392057776,808.6610594764352]))
      dst.should.be.identicalTo([-264042.57608104264,-463734.26427327306,907361.8605148251,559119.3661495624])

      dst = F(4)
      DSP.mul(dst, F([953.7175842560828,132.36253685317934,296.11885733902454,806.1646881978959]), F([-364.22319430857897,890.7485678792,-932.0990485139191,-682.5220347382128]))
      dst.should.be.identicalTo([-347366.06500601175,117901.74014282733,-276012.1051727337,-550225.1633229248])

      dst = F(4)
      DSP.mul(dst, F([56.375515880063176,740.7926782034338,19.654368283227086,774.0685441531241]), F([469.6681913919747,235.7547441497445,-295.24840600788593,463.6164754629135]))
      dst.should.be.identicalTo([26477.786582178822,174645.38831785455,-5802.920906714747,358870.93020698003])

      dst = F(4)
      DSP.mul(dst, F([502.33335071243346,609.4308877363801,749.4483531918377,685.2339645847678]), F([-969.4670485332608,-364.20198529958725,310.19944651052356,-891.3870551623404]))
      dst.should.be.identicalTo([-486995.63089500624,-221955.9392164795,232478.4643483314,-610808.6857884317])

      dst = F(4)
      DSP.mul(dst, F([471.182803157717,218.3964855503291,752.1887612529099,653.8821931462735]), F([181.31699413061142,-904.9974335357547,-246.8463983386755,574.8008396476507]))
      dst.should.be.identicalTo([85433.44955459281,-197648.25891627636,-185675.08658611067,375852.0336511253])

  describe ".div", ->
    it "should provide correct results", ->
      dst = F(4)
      DSP.div(dst, F([153,91,436,558]), F([947,70,264,703]))
      dst.should.be.identicalTo([0.16156282998944033,1.3,1.6515151515151516,0.7937411095305832])

      dst = F(4)
      DSP.div(dst, F([422,852,564,635]), F([296,1,54,578]))
      dst.should.be.identicalTo([1.4256756756756757,852,10.444444444444445,1.0986159169550174])

      dst = F(4)
      DSP.div(dst, F([410,733,902,27]), F([877,284,917,573]))
      dst.should.be.identicalTo([0.467502850627138,2.5809859154929575,0.9836423118865867,0.04712041884816754])

      dst = F(4)
      DSP.div(dst, F([803,675,180,366]), F([779,698,156,482]))
      dst.should.be.identicalTo([1.030808729139923,0.9670487106017192,1.1538461538461537,0.7593360995850622])

      dst = F(4)
      DSP.div(dst, F([184,18,546,26]), F([309,391,215,930]))
      dst.should.be.identicalTo([0.5954692556634305,0.04603580562659847,2.5395348837209304,0.02795698924731183])

      dst = F(4)
      DSP.div(dst, F([20,837,848,945]), F([372,782,310,655]))
      dst.should.be.identicalTo([0.053763440860215055,1.0703324808184143,2.735483870967742,1.4427480916030535])

      dst = F(4)
      DSP.div(dst, F([515,789,461,608]), F([539,953,545,675]))
      dst.should.be.identicalTo([0.9554730983302412,0.8279118572927597,0.8458715596330275,0.9007407407407407])

      dst = F(4)
      DSP.div(dst, F([484,180,162,451]), F([303,409,408,806]))
      dst.should.be.identicalTo([1.5973597359735974,0.4400977995110024,0.39705882352941174,0.5595533498759305])

      dst = F(4)
      DSP.div(dst, F([129,2,602,747]), F([616,412,447,286]))
      dst.should.be.identicalTo([0.20941558441558442,0.0048543689320388345,1.3467561521252795,2.611888111888112])

    it "should be able to deal with negative values", ->
      dst = F(4)
      DSP.div(dst, F([687,634,442,357]), F([-260,-52,-55,-335]))
      dst.should.be.identicalTo([-2.6423076923076922,-12.192307692307692,-8.036363636363637,-1.0656716417910448])

      dst = F(4)
      DSP.div(dst, F([735,292,118,754]), F([-904,-101,-202,-896]))
      dst.should.be.identicalTo([-0.8130530973451328,-2.891089108910891,-0.5841584158415841,-0.8415178571428571])

      dst = F(4)
      DSP.div(dst, F([482,800,998,405]), F([-906,-704,-55,-160]))
      dst.should.be.identicalTo([-0.5320088300220751,-1.1363636363636365,-18.145454545454545,-2.53125])

      dst = F(4)
      DSP.div(dst, F([254,578,295,849]), F([-736,-395,-589,-564]))
      dst.should.be.identicalTo([-0.3451086956521739,-1.4632911392405064,-0.5008488964346349,-1.5053191489361701])

      dst = F(4)
      DSP.div(dst, F([282,544,314,860]), F([-536,-71,-950,-378]))
      dst.should.be.identicalTo([-0.5261194029850746,-7.661971830985915,-0.33052631578947367,-2.2751322751322753])

      dst = F(4)
      DSP.div(dst, F([912,617,702,167]), F([-782,-279,-385,-4]))
      dst.should.be.identicalTo([-1.1662404092071612,-2.2114695340501793,-1.8233766233766233,-41.75])

      dst = F(4)
      DSP.div(dst, F([125,807,450,576]), F([-806,-430,-648,-360]))
      dst.should.be.identicalTo([-0.15508684863523572,-1.8767441860465117,-0.6944444444444444,-1.6])

      dst = F(4)
      DSP.div(dst, F([998,846,654,563]), F([-514,-816,-948,-385]))
      dst.should.be.identicalTo([-1.9416342412451362,-1.036764705882353,-0.689873417721519,-1.4623376623376623])

      dst = F(4)
      DSP.div(dst, F([340,822,720,333]), F([-161,-388,-893,-106]))
      dst.should.be.identicalTo([-2.111801242236025,-2.118556701030928,-0.8062709966405375,-3.141509433962264])

    it "should be able to deal with decimal values", ->
      dst = F(4)
      DSP.div(dst, F([443.40162537992,505.3492677398026,805.8234371710569,520.9516226314008]), F([590.2828895486891,-163.4230064228177,-72.34945520758629,156.4507158473134]))
      dst.should.be.identicalTo([0.7511680132197806,-3.0922773898329403,-11.137933725402279,3.329812968959622])

      dst = F(4)
      DSP.div(dst, F([31.875606393441558,66.64635892957449,935.5970562901348,213.68609624914825]), F([-16.189795453101397,-25.194481946527958,-933.8342412374914,857.9831472598016]))
      dst.should.be.identicalTo([-1.9688702359321848,-2.6452760200040153,-1.001887717300136,0.2490562861655405])

      dst = F(4)
      DSP.div(dst, F([706.8524439819157,367.82184964977205,577.8391426429152,825.4014370031655]), F([-316.2449807859957,687.1409518644214,-150.01793997362256,204.38342075794935]))
      dst.should.be.identicalTo([-2.23514201624672,0.5352931573234866,-3.8518002763170585,4.0384950694248625])

      dst = F(4)
      DSP.div(dst, F([425.94985221512616,937.2258859220892,799.5377774350345,347.69049496389925]), F([-27.004788164049387,502.77163507416844,483.7187039665878,-701.2774609029293]))
      dst.should.be.identicalTo([-15.773123256052036,1.864118459633926,1.6528982048423364,-0.4957959072522174])

      dst = F(4)
      DSP.div(dst, F([567.9985783062875,574.5479988399893,143.18934851326048,155.33061930909753]), F([121.2244350463152,251.0056416504085,152.627217117697,-273.2233493588865]))
      dst.should.be.identicalTo([4.685512273901521,2.2889844031481923,0.9381639213328603,-0.5685115114560229])

      dst = F(4)
      DSP.div(dst, F([473.4143312089145,873.4302809461951,841.0938433371484,194.58892638795078]), F([-243.81056986749172,469.8268729262054,-220.95067100599408,-853.686073794961]))
      dst.should.be.identicalTo([-1.9417301369100193,1.8590470900615828,-3.8067041820132363,-0.2279396752051121])

      dst = F(4)
      DSP.div(dst, F([790.1885714381933,675.7073332555592,831.4406194258481,156.04943875223398]), F([17.29061594232917,855.112127494067,-18.787738867104053,-748.4101136215031]))
      dst.should.be.identicalTo([45.70042930071289,0.7901973455057185,-44.25442706581575,-0.20850792354625178])

      dst = F(4)
      DSP.div(dst, F([63.616198720410466,545.5304626375437,958.4058877080679,979.7758907079697]), F([-382.2185038588941,-164.01294665411115,-938.8859397731721,-356.21201945468783]))
      dst.should.be.identicalTo([-0.16643934837831934,-3.326142684260282,-1.0207905423949704,-2.7505413551397657])

      dst = F(4)
      DSP.div(dst, F([617.4267448950559,151.40298730693758,686.5522316657007,384.9977261852473]), F([-223.1875266879797,800.6582409143448,791.7783963494003,614.1862752847373]))
      dst.should.be.identicalTo([-2.766403454787283,0.18909814396469168,0.8671014956093033,0.6268419560609068])

  describe ".madd", ->
    it "should provide correct results", ->
      dst = F(4)
      DSP.madd(dst, F([659,581,365,923]), F([198,118,674,501]), F([189,871,579,111]))
      dst.should.be.identicalTo([38081,103359,390611,56534])

      dst = F(4)
      DSP.madd(dst, F([653,4,161,303]), F([928,602,909,387]), F([261,239,757,487]))
      dst.should.be.identicalTo([242861,143882,688274,188772])

      dst = F(4)
      DSP.madd(dst, F([74,2,957,291]), F([732,968,527,598]), F([965,971,810,507]))
      dst.should.be.identicalTo([706454,939930,427827,303477])

      dst = F(4)
      DSP.madd(dst, F([527,343,431,477]), F([81,945,180,578]), F([933,525,25,562]))
      dst.should.be.identicalTo([76100,496468,4931,325313])

      dst = F(4)
      DSP.madd(dst, F([238,736,278,490]), F([548,804,506,644]), F([962,809,145,5]))
      dst.should.be.identicalTo([527414,651172,73648,3710])

      dst = F(4)
      DSP.madd(dst, F([974,757,595,144]), F([909,334,436,163]), F([459,865,66,90]))
      dst.should.be.identicalTo([418205,289667,29371,14814])

      dst = F(4)
      DSP.madd(dst, F([127,694,58,810]), F([231,873,396,293]), F([605,594,335,983]))
      dst.should.be.identicalTo([139882,519256,132718,288829])

      dst = F(4)
      DSP.madd(dst, F([814,216,876,829]), F([967,96,935,742]), F([643,183,717,438]))
      dst.should.be.identicalTo([622595,17784,671271,325825])

      dst = F(4)
      DSP.madd(dst, F([677,639,215,964]), F([391,564,408,293]), F([595,200,855,273]))
      dst.should.be.identicalTo([233322,113439,349055,80953])

    it "should be able to deal with negative values", ->
      dst = F(4)
      DSP.madd(dst, F([37,408,706,211]), F([-125,-679,-386,-981]), F([-18,-625,-920,-507]))
      dst.should.be.identicalTo([2287,424783,355826,497578])

      dst = F(4)
      DSP.madd(dst, F([251,968,240,786]), F([-956,-988,-133,-747]), F([-265,-77,-723,-452]))
      dst.should.be.identicalTo([253591,77044,96399,338430])

      dst = F(4)
      DSP.madd(dst, F([565,915,47,716]), F([-361,-42,-477,-200]), F([-181,-270,-914,-30]))
      dst.should.be.identicalTo([65906,12255,436025,6716])

      dst = F(4)
      DSP.madd(dst, F([511,208,683,102]), F([-186,-662,-613,-665]), F([-929,-930,-653,-838]))
      dst.should.be.identicalTo([173305,615868,400972,557372])

      dst = F(4)
      DSP.madd(dst, F([835,32,894,119]), F([-123,-227,-287,-529]), F([-914,-924,-150,-208]))
      dst.should.be.identicalTo([113257,209780,43944,110151])

      dst = F(4)
      DSP.madd(dst, F([536,170,35,731]), F([-506,-638,-727,-969]), F([-330,-550,-866,-231]))
      dst.should.be.identicalTo([167516,351070,629617,224570])

      dst = F(4)
      DSP.madd(dst, F([22,474,132,902]), F([-95,-673,-992,-794]), F([-450,-264,-910,-188]))
      dst.should.be.identicalTo([42772,178146,902852,150174])

      dst = F(4)
      DSP.madd(dst, F([175,856,518,663]), F([-799,-490,-518,-430]), F([-370,-498,-165,-730]))
      dst.should.be.identicalTo([295805,244876,85988,314563])

      dst = F(4)
      DSP.madd(dst, F([848,274,421,678]), F([-19,-377,-331,-943]), F([-656,-223,-180,-898]))
      dst.should.be.identicalTo([13312,84345,60001,847492])

    it "should be able to deal with decimal values", ->
      dst = F(4)
      DSP.madd(dst, F([431.5957787912339,544.194750720635,385.1467010099441,439.93882928043604]), F([582.8954069875181,-274.6881591156125,-282.0429103448987,-168.9471616409719]), F([610.763318836689,-319.471369497478,-622.3394768312573,-616.8598760850728]))
      dst.should.be.identicalTo([356442.72908515035,88299.19712812651,175911.5839690194,104656.66402405512])

      dst = F(4)
      DSP.madd(dst, F([570.8431242965162,74.94604936800897,626.6574901528656,840.6733935698867]), F([940.4168813489377,-790.0822232477367,-212.75237062945962,-640.0857735425234]), F([-719.9386227875948,494.03825402259827,466.84107137843966,498.7947535701096]))
      dst.should.be.identicalTo([-676471.5912802627,-390255.89605823654,-98694.88715280694,-318430.75228430604])

      dst = F(4)
      DSP.madd(dst, F([92.45079406537116,696.5452486183494,510.24883007630706,797.0771591644734]), F([930.6814200244844,-6.8902019411325455,-220.65379517152905,-713.052982930094]), F([-336.5197740495205,307.66592686995864,-702.003170736134,-599.6935912407935]))
      dst.should.be.identicalTo([-313100.250384661,-1423.3351179213832,155409.91267545117,428410.38123747276])

      dst = F(4)
      DSP.madd(dst, F([374.0670548286289,57.288607116788626,251.43136084079742,179.85483794473112]), F([600.1510680653155,-978.7263008765876,732.523919083178,-694.3527371622622]), F([233.7017459794879,436.11767096444964,456.7373814061284,877.1711410954595]))
      dst.should.be.identicalTo([140630.41951314732,-426782.5462428318,334822.48798024625,-608886.3279414325])

      dst = F(4)
      DSP.madd(dst, F([629.4662307482213,106.25358694233,580.4366832599044,82.82434428110719]), F([423.05148392915726,-701.9113972783089,-476.29577992483974,-321.59393234178424]), F([-657.7629540115595,977.6374991051853,-693.8485628925264,339.72910698503256]))
      dst.should.be.identicalTo([-277638.12753746804,-686108.6494416497,331057.579095885,-109171.99510199823])

      dst = F(4)
      DSP.madd(dst, F([73.35627754218876,935.4177140630782,312.0442742947489,261.5334508009255]), F([337.4871136620641,777.7401339262724,-730.0009145401418,29.064410366117954]), F([-601.7460920847952,31.913117971271276,458.77108070999384,126.88859086483717]))
      dst.should.be.identicalTo([-203008.19549758197,25755.530359044533,-334591.26420856995,3949.475526474999])

      dst = F(4)
      DSP.madd(dst, F([716.5045524016023,691.6872209403664,506.2328700441867,977.1110825240612]), F([753.1423717737198,-719.1230794414878,544.766194652766,589.9348328821361]), F([587.9540359601378,-670.6563835032284,-374.8906212858856,-643.7674015760422]))
      dst.should.be.identicalTo([443529.60168935073,482976.1709728734,-203721.50429887892,-378803.7033812054])

      dst = F(4)
      DSP.madd(dst, F([588.8720080256462,501.60171859897673,185.99543627351522,444.9916537851095]), F([-110.27760896831751,457.66721526160836,-79.30542528629303,22.378692403435707]), F([-266.2891633808613,496.5184316970408,-843.0924704298377,890.065984800458]))
      dst.should.be.identicalTo([29954.60423984068,227741.80967944473,67047.80235938322,20363.50454639564])

      dst = F(4)
      DSP.madd(dst, F([111.87649378553033,321.18971226736903,117.16574430465698,992.9154941346496]), F([259.1718412004411,-17.270153388381004,-474.5310451835394,-623.6120769754052]), F([-778.3735319972038,930.276561062783,82.05322409048676,355.9029852040112]))
      dst.should.be.identicalTo([-201620.62493562026,-15744.829190902481,-38819.6364440332,-220952.4843106857])