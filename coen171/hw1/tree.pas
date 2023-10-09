program treeCode(input, output);

    type 
    tree = ^node;
    node = record
        info: Integer;
        left: tree;
        right: tree;
    end;

    function insert(root: tree; value: Integer): tree;
    begin 
        if root = nil then 
        begin 
            new(root);
            root^.left := nil;
            root^.right := nil;
            root^.info := value;
        end
        else if root^.info < value then
            root^.right := insert(root^.right, value)
        else if root^.info > value then
            root^.left := insert(root^.left, value);
        insert := root;
    end;

    function member(root: tree; value: Integer): Integer;
    begin   
        if root = nil then
            member := 0
        else if value < root^.info then  
            member := member(root^.left, value)
        else if value > root^.info then 
            member := member(root^.right, value)
        else
            member := 1;
    end;

    var t: tree;
    var x: integer;

begin
    t := nil;
    ReadLn(x);

    while x <> -1 do
    begin
        t := insert(t, x);
        ReadLn(x);
    end;

    ReadLn(x);

    while x <> -1 do
    begin
        if member(t, x) <> 0 then
            writeln('True')
        else
            writeln('False');
        ReadLn(x);
    end
end.
