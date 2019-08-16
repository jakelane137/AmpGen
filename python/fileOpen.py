with open("fit.log") as file:
    for line in file:
        #print(line)
        spl = line.split()
        #print(len(spl))
        #if len(spl) == 4:
         #   print(spl)
        if "Parameter" in spl:
            #print(spl)
            print(f"{spl[1]} = {spl[3]} ± {spl[4]}")
