n,x,y=gets.split.map(&:to_i)
l=0;r=9**9;res=r
while l <= r
  mid=(l+r)/2
  if (x+mid)*100>=y*n
    res=mid
    r=mid-1
  else
    l=mid+1
  end
end
p res
