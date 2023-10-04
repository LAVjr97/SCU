import unittest

class vacuum:
    #initializes current state, sequence, and cost to 0
    def __init__(self, state, seq):
        self.state = state
        self.seq = seq
        self.cost = 0

    #checks both tiles for a clean state
    def goal_test(self, state):
        if(state[0] == "clean" and state[1] == "clean"):
            return True
        else:
            return False

    #if the current tile is dirty, take action, else move depending on the tile its on 
    def action(self, state):
        cPos = state[2]

        if(state[cPos] == "dirty"):
            return "suck"
        
        if(cPos == 1):
            return "left"
        
        if(cPos == 0):
            return "right"
        
    #updates state of the tile, action sequence, and cost based on the action taken 
    def update(self, state, act):
        cPos = state[2]

        if(act == "suck"):
            state[cPos] = "clean"

        if(act == "left"):
            state[2] = 0

        if(act == "right"):
            state[2] = 1

        self.cost += 1
        self.seq.append(act)

        return

    def run(self, state):
        while(1):
            if(self.goal_test(state) == True):
                return self.seq 
            else:
                act = self.action(state)
                self.update(state, act) 
            
class Testlab2(unittest.TestCase):

    def test1_lab2(self):
        condition = vacuum(["clean", "clean", 0], [])
        tSeq = vacuum.run(condition, condition.state)
        tCost = condition.cost 
        self.assertEqual(tSeq, [])
        self.assertEqual(tCost, 0)
    
    def test2_lab2(self):
        condition = vacuum(["clean", "clean", 1], [])
        tSeq = vacuum.run(condition, condition.state)
        tCost = condition.cost 
        self.assertEqual(tSeq, [])
        self.assertEqual(tCost, 0)
    
    def test3_lab2(self):
        condition = vacuum(["dirty", "clean", 0], []) 
        tSeq = vacuum.run(condition, condition.state) 
        tCost = condition.cost 
        self.assertEqual(tSeq, ["suck"])
        self.assertEqual(tCost, 1)
    

    def test4_lab2(self):
        condition = vacuum(["dirty", "clean", 1], [])
        tSeq = vacuum.run(condition, condition.state)
        tCost = condition.cost 
        self.assertEqual(tSeq, ["left", "suck"]) 
        self.assertEqual(tCost, 2) 

    def test5_lab2(self): 
        condition = vacuum(["clean", "dirty", 0], []) 
        tSeq = vacuum.run(condition, condition.state) 
        tCost = condition.cost  
        self.assertEqual(tSeq, ["right", "suck"]) 
        self.assertEqual(tCost, 2)

    def test6_lab2(self):
        condition = vacuum(["clean", "dirty", 1], [])
        tSeq = vacuum.run(condition, condition.state)
        tCost = condition.cost 
        self.assertEqual(tSeq, ["suck"])
        self.assertEqual(tCost, 1)

    def test7_lab2(self):
        condition = vacuum(["dirty", "dirty", 0], [])
        tSeq = vacuum.run(condition, condition.state)
        tCost = condition.cost 
        self.assertEqual(tSeq, ["suck", "right", "suck"])
        self.assertEqual(tCost, 3)

    def test8_lab2(self):
        condition = vacuum(["dirty", "dirty", 1], [])
        tSeq = vacuum.run(condition, condition.state)
        tCost = condition.cost 
        self.assertEqual(tSeq, ["suck", "left", "suck"])
        self.assertEqual(tCost, 3)

if __name__== '__main__':
    unittest.main()