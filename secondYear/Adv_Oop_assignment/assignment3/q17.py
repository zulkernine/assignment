import heapq

class PriorityQueue:
    def __init__(self):
        self._queue = []
        self._entry_count = 0

    def push(self,item,priority):
        heapq.heappush(self._queue,(priority,self._entry_count,item))
        self._entry_count += 1

    def pop(self):
        return heapq.heappop(self._queue)[-1]

def main():
    mails = [
        ("lfas@gmail.com", "aflsjd asdfjk klafjsd ads;lkj sadfjk dfjk f dff  sa jak asff hl jksdaff sdf. laksdfl jksdf jsd kj f"),
        ("hgfb@gmail.com","aflsjd asdfjkj jak asdjksadfjk dfjkksdafhsddjk jksf dk df. laksdfl jksdf jsd kj f"),
        ("rdsf@gmail.com","aflsjd asdfjk klafjsd ads;lkj sk  ads;ladfjk dfjksa jak asdjk jksf dk dff hl jksdaff sdf. laksdfl jksdf jsd kj f"),
        ("dfcy@gmail.com", "aflsjd asdfjk klafjsd ads;lkj sadfjk dfjksa jakk dff hl jksdaff sdf. laksdfl jksdf jsd kj f"),
        ("nsdf@gmail.com", "aflsjd asdfjk klafjsd ads;lkj sadfjk dfjksa jak asd f"),
        ("ysdv@gmail.com", "aflsjd asdfjk klafjsd ads;")
    ]

    pq = PriorityQueue()

    for mail in mails:
        pq.push(mail,len(mail[1]))
    
    for _ in range(len(mails)):
        mail = pq.pop()
        print("EMAIL: ",mail[0],"\tBODY: ",mail[1])

if __name__ == '__main__' :
    main()

