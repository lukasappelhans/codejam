
class ProblemSolver

    def initialize(n, array)
        @array = array
        @n = n
        @steps = -1
        @countedArray = Array.new(n) { Array.new(n) }
        
        revealed = Array.new(n) { Array.new(n) }
        
        n.times do |i|
            n.times do |j|
                if @array[i][j] == "*"
                   revealed[i][j] = "R" 
                   @countedArray[i][j] = "*"
                else 
                    minesCount = 0
                    ([0, i - 1].max..[@n - 1, i + 1].min).each do |blocki|
                        ([0, j - 1].max..[@n - 1, j + 1].min).each do |blockj|
                            unless (blocki == i && blockj == j) || @array[blocki][blockj] == "."
                                minesCount = minesCount + 1
                            end
                        end
                    end
                    @countedArray[i][j] = minesCount
                    revealed[i][j] = "." 
                end
            end
        end
        count = 0
        solve(count, revealed)
    end
    
    def solve(c, r)
        count = c + 1
        if @steps != -1 && count >= @steps
            return
        end
        
        #puts r.inspect
        
        candidates = Hash.new
        
        #puts "Search new candidates:" 
        #Try to identify big blocks of unidentified cells
        #TODO: Recursively open the ones!!!!
        @n.times do |i|
            @n.times do |j|
                unless @countedArray[i][j] != 0
                    reveals = 0;
                    ([0, i - 1].max..[@n - 1, i + 1].min).each do |blocki|
                        ([0, j - 1].max..[@n - 1, j + 1].min).each do |blockj|
                            unless r[blocki][blockj] == "R"
                                reveals = reveals + 1
                            end
                        end
                    end
                    unless reveals <= 1
                        candidates[[i, j]] = reveals;
                    end
                end
            end
        end
        
        
        if candidates.empty?
            clicks = 0
            @n.times do |i|
                @n.times do |j|
                    unless r[i][j] == "R"
                        clicks = clicks + 1
                    end
                end
            end
            @steps = count + clicks - 1
            #puts "End with " + @steps.to_s
            return
        end
        
        candidates = candidates.sort_by{ |point, value| value }.reverse
        
        lastvalue = -1
        #Try all candidates
        candidates.each do |point, value|
            unless value == lastvalue || lastvalue == -1
                break
            end
            lastvalue = value
            x = point[0]
            y = point[1]
            
            #puts "Chose " + point.inspect + " reveals " + value.to_s + " count " + @countedArray[x][y].to_s + " depth " + count.to_s + " steps " + @steps.to_s
            #puts r[x][y]
            
            revealed = []
            
            r.each { |el| revealed.push(el.dup) } 
            
            revealed[x][y] = "R"
            #puts revealed.inspect
            reveal(revealed, x, y)
            #puts revealed.inspect
            #Check if everything is revealed
            ended = true
            @n.times do |i|
                @n.times do |j|
                    if revealed[i][j] == "."
                        ended = false
                        break
                    end
                end
                unless ended
                    break
                end
            end
            if ended 
                #if one candidate solves it, stop everything, as no other candidate can do it quicker
                @steps = count
                #puts "ended steps " + count.to_s
                break
            else
                solve(count, revealed)
                break
            end
        end
    end
    
    def getSteps
        @steps
    end
    
    def reveal(revealed, x, y)
        if @countedArray[x][y] == 0
            if x != 0 && y != 0 && revealed[x - 1][y - 1] != "R"
                revealed[x - 1][y - 1] = "R"
                
                if @countedArray[x - 1][y - 1] == 0
                    reveal(revealed, x - 1, y - 1)
                end
            end
            if x != 0 && revealed[x - 1][y] != "R"
                revealed[x - 1][y] = "R"
                if @countedArray[x - 1][y] == 0
                    reveal(revealed, x - 1, y)
                end
            end
            if x != 0 && y < @n - 1 && revealed[x - 1][y + 1] != "R"
                revealed[x - 1][y + 1] = "R"
                if @countedArray[x - 1][y + 1] == 0
                    reveal(revealed, x - 1, y + 1)
                end
            end
            if y != 0 && revealed[x][y - 1] != "R"
                revealed[x][y - 1] = "R"
                if @countedArray[x][y - 1] == 0
                    reveal(revealed, x, y - 1)
                end
            end
            if y < @n - 1 && revealed[x][y + 1] != "R"
                revealed[x][y + 1] = "R"
                if @countedArray[x][y + 1] == 0
                    reveal(revealed, x, y + 1)
                end
            end
            if x < @n - 1 && y != 0 && revealed[x + 1][y - 1] != "R"
                revealed[x + 1][y - 1] = "R"
                if @countedArray[x + 1][y - 1] == 0
                    reveal(revealed, x + 1, y - 1)
                end
            end
            if x < @n - 1 && revealed[x + 1][y] != "R"
                revealed[x + 1][y] = "R"
                if @countedArray[x + 1][y] == 0
                    reveal(revealed, x + 1, y)
                end
            end
            if x < @n - 1 && y < @n - 1 && revealed[x + 1][y + 1] != "R"
                revealed[x + 1][y + 1] = "R"
                if @countedArray[x + 1][y + 1] == 0
                    reveal(revealed, x + 1, y + 1)
                end
            end
        end
    end
end


filename = ARGV[0]

file = File.open(filename)
num = file.readline
casenum = 1
while !file.eof?
   n = file.readline
   problem = []
   n.to_i.times do |i|
       line = file.readline
       problem.push(line.gsub("\n",'').split(//))
   end
   start = Time.now
   solver = ProblemSolver.new(n.to_i, problem)
   final = Time.now
   puts "Case #" + casenum.to_s + ": " + solver.getSteps.to_s
   #break
   casenum = casenum + 1
end
