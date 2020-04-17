class arr:
	def __init__(self,data,priority):
		self.data = data
		self.priority = priority
		self.index = -1

class priorityQueue:
	def __init__(self):
		self.Q = list()
		self.heapSize = -1

	def heapify(self,i):
		small = i
		left = 2*i+1
		right = 2*i+2
		
		if self.heapSize >= left and self.Q[left].priority < self.Q[small].priority:
			small = left
			
		if self.heapSize >= right and self.Q[right].priority < self.Q[small].priority:
			small = right
	
		if small != i:
			self.swap(small,i)
			self.heapify(small)

	def swap(self,i,j):
		self.Q[i].data ,self.Q[j].data = self.Q[j].data ,self.Q[i].data
		self.Q[i].priority ,self.Q[j].priority = self.Q[j].priority ,self.Q[i].priority
		self.Q[i].index ,self.Q[j].index = self.Q[j].index ,self.Q[i].index

	def parent(self,i):
		return (i-1)//2

	def enQueue(self,data,priority):
		self.heapSize += 1
		index = self.heapSize

		
		self.Q.append(arr(data,priority))
		self.Q[index].index = index
		p = self.parent(index)
		while  p >= 0:
			if  self.Q[p].priority > self.Q[index].priority:
				self.swap(p,index)
				self.Q[index].index = index 
			index = p

			p = self.parent(index)


	def printHeap(self):
		for i in range(self.heapSize+1):
			# print(self.Q[i].data,end = " ")
			print(str(self.Q[i].data)+"=>"+str(self.Q[i].priority),end = " ")
		print(" ")

	def deQueue(self):
		if self.isEmpty():
			return -1
		temp = self.Q[0]
		self.swap(self.heapSize,0)
		self.heapSize -= 1
		self.heapify(0)
		
		return temp

	def isEmpty(self):
		if self.heapSize == -1:
			return True
		return False

	def updatePriority(self,data,priority):
		for i in self.Q:
			if i.data == data:
				i.priority = priority


if __name__ == "__main__":

	pq =priorityQueue()
	pq.enQueue(1,10)
	print(pq.heapSize)
	pq.printHeap()
	pq.deQueue()
	pq.printHeap()
	print(pq.heapSize)
	pq.enQueue(2,3)
	pq.enQueue(5,6)
	pq.enQueue(3,9)
	pq.printHeap()
	a = pq.deQueue()
	print(a.data,a.priority)
	pq.printHeap()
	a = pq.deQueue()
	# print(a.data,a.priority)
	pq.printHeap()
