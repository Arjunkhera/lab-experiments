
def xor(op1,op2):
  result=[]
  for i in range(1,len(op2)):
      if op1[i] is op2[i]:
          result.append('0')
      else:
          result.append('1')

  return ''.join(result)

def remainder(dividend,divisor='1101'):
    k=len(divisor)
    temp=dividend[:k]

    while k<len(dividend):

        if temp[0] is '1':
            temp= xor(divisor,temp) + dividend[k]
        else:
            temp= xor('0'*k,temp) + dividend[k]

        k+=1
    if temp[0] is '1':
        temp= xor(divisor,temp)
    else:
        temp= xor('0'*k,temp)
    return temp

print("Enter the data to be sent: ")
data=str(input())
print("Enter the data recieved at the reciever side: ")
recieved=str(input())

div='1101'
data=data + remainder(data+'0'*(len(div)-1),div)
remain=remainder(recieved)

correct=True
for i in remain:
    if i is '1':
        correct=False
        break

if(correct):
    print("According to CRC the recieved data is correct")
else:
    print("The Data is Corrupt. Call for Retransmission. The data should have been ",data,".")
