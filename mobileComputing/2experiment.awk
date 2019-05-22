BEGIN{
  count=0;
}

{
  if($1 == "d")
    count++;
}

END{
  printf("The total no of packet drop is:%d\n\n",count);
}
