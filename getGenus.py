import sys


inFile = open("plants2.data", "r")
count = 0
genus = {}

#put all the genus's in a dictionary
for line in inFile:
    splitLine = line.split()
    if splitLine[0] not in genus:
       genus[splitLine[0]] =  1
    else:
       genus[splitLine[0]] += 1
inFile.close()
#print len(genus)
#sanity check
#for value in genus.values():
#    count += value
#print count

k=-1
cluster = {}
doNothing = True;
#infile2 = open("results1.txt", "r")
infile2 = open(sys.argv[1], "r")

for line in infile2:
    splitLine = line.split()
    if len(splitLine) != 0:
        if splitLine[0] == "Cluster:":
            cluster[splitLine[1]] = {}
            k+=1
        elif splitLine[0] == "The":
            doNothing = True
        else:
            if splitLine[0] not in cluster[str(k)]:
                cluster[str(k)][splitLine[0]] = 1
            else:
                cluster[str(k)][splitLine[0]] += 1

#make sure everything got put in correctly
#for key in cluster.keys():
#    print "Cluster = %s" %key
#    for key2 in cluster[key].keys():
#        print "Genus: %s \t NumberInCluster: %d" %(key2, cluster[key][key2])

#print genus

j=0
correctCount = 0
while j < 20:
    print "Cluster = %d" %j
    for key in cluster[str(j)].keys():
        if float(cluster[str(j)][key])/int(genus[key]) >= .75:
            correctCount +=1
        print "Genus: %s \t NumberInCluster: %d \t PercentageInCluster: %f" %(key, cluster[str(j)][key], (float(cluster[str(j)][key])/int(genus[key])))
    j+=1

print correctCount
avg = correctCount/float(len(genus))
print "The average of This data set is: %f\n" %avg
