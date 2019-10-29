
def miniMaxEvalauate(board,player):

    opponent = { Player_O : Player_X, Player_X : Player_O }

    winning_rows = [[0,1,2],[3,4,5],[6,7,8], # vertical
                    [0,3,6],[1,4,7],[2,5,8], # horizontal
                    [0,4,8],[2,4,6]]         # diagonal

    count=0

    clone_pieces=[Empty]*9 # Initialize an empty chessboard

    # Copy the current chessboard
    for i in range(9):
        clone_pieces=board.pieces

    # fill it into the clone chessboard
    for pos in range(9):
        if clone_pieces[pos] == Empty:
            clone_pieces[pos]=player

    # analyse ur point value
    for row in winning_rows:
        if allEqual([clone_pieces for i in row]):
            count+=1



    clone_pieces2=[Empty]*9

    for i in range(9):
        clone_pieces2=board.pieces

    for pos in range(9):
        if clone_pieces2[pos] == Empty:
            clone_pieces2[pos]=opponent[player]
    for row in winning_rows:
        if allEqual([clone_pieces2 for i in row]):
            count-=1

    return count

def comp2(board,player):

    t0 = time.time()
    board.output() # print the chessboard

    def miniMax(board, depth, p=player):

        opponent = { Player_O : Player_X, Player_X : Player_O }
        moves=[]
        outcomes=[]

        # return if game over
        if board.gameOver():
            if board.gameOver()== player:
                return +100
            if board.gameOver()== opponent[player]:
                return -100
            return 0

        if depth!=0:

            depth-=1
            for move in board.getValidMoves():

                board.makeMove(move, p)
                point=miniMax(board,depth,opponent[p])
                outcomes+=[point]
                moves+=[move]
                board.undoMove(move)
        else:
            return miniMaxEvalauate2(board,player)

        if p != player:
            #return min(outcomes)
            min_element = 100
            n=0
            for o in outcomes:
                if o == -100:
                    board.bestmove=moves[n]
                    return o
                min_element = min(o,min_element)
                if o==min_element:
                    board.bestmove=moves[n]
                n+=1
            return min_element
        else:
            #return max(outcomes)
            max_element = -100
            n=0
            for o in outcomes:
                if o == +100:
                    board.bestmove=moves[n]
                    return o
                max_element = max(o,max_element)
                if o==max_element:
                    board.bestmove=moves[n]
                n+=1
            return max_element

    miniMax(board, 3)

    board.makeMove(board.bestmove, player)
    print ("computer move: %0.3f ms" % ((time.time()-t0)*1000))

def miniMaxEvalauate2(board,player):

    opponent = { Player_O : Player_X, Player_X : Player_O }

    winning_rows = [[0,1,2],[3,4,5],[6,7,8], # vertical
                    [0,3,6],[1,4,7],[2,5,8], # horizontal
                    [0,4,8],[2,4,6]]         # diagonal

    count=0

    clone_pieces=[Empty]*9

    for i in range(9):
        clone_pieces=board.pieces

    for pos in range(9):
        if clone_pieces[pos] == Empty:
            clone_pieces[pos]=player
    for row in winning_rows:
        flag=0
        for i in row:
            if(clone_pieces==opponent[player]):
                flag+=1
        if (flag==0):
            count+=1
        if (flag==2):
            count-=4

    clone_pieces2=[Empty]*9

    for i in range(9):
        clone_pieces2=board.pieces

    for pos in range(9):
        if clone_pieces2[pos] == Empty:
            clone_pieces2[pos]=opponent[player]
    for row in winning_rows:
        flag=0
        for i in row:
            if(clone_pieces2==opponent[player]):
                flag+=1
        if (flag==3):
            count-=1

    return count
