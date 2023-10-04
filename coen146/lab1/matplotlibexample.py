# import the neccessary libraries required for the plotting of a graph, such as matplotlib
import matplotlib.pyplot as plt

#list of the x-values and the y-values we want to plot
x = [10,20,30,40,50,60,70,80,90,100]
y = [.31,.15,.20,.52,.25,.22,.23,.26,.31,.27]

#the plot() function creates the plot
plt.plot(x,y) #make sure that the x and the y list contains the same number of elements 

#xlabel() and ylabel() functions helps in renameing the titles of the x and y axis 
plt.ylabel('Time (x10^-4)(s)') 
plt.xlabel('File Size (Bytes)') 

#include the title of the graph using the title() function 
plt.title('Impact of File Size on Time to Copy')

#saves the graph as a file 
plt.savefig("impactgraph.png")

#shows the output of the graph on the screen
plt.show()
