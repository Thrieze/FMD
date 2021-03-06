  function GetTurkcraftPageNumber: Boolean;
  var
    s: String;
    i: Cardinal;
    l: TStringList;
  begin
    l := TStringList.Create;
    parse := TStringList.Create;
    s := DecodeUrl(FillMangaSiteHost(TURKCRAFT_ID, URL) + '/1');
    Result := GetPage(TObject(l),
      s,
      Task.Container.manager.retryConnect);
    Parser := THTMLParser.Create(PChar(l.Text));
    Parser.OnFoundTag := @OnTag;
    Parser.OnFoundText := @OnText;
    Parser.Exec;
    Parser.Free;
    if parse.Count > 0 then
    begin
      Task.Container.pageNumber := 0;
      for i := 0 to parse.Count - 1 do
      begin
        if (Pos('title="Next Page"', parse[i]) > 0) then
        begin
          s := parse[i - 5];
          Task.Container.PageNumber := StrToInt(TrimLeft(TrimRight(s)));
          Break;
        end;
      end;
    end;
    parse.Free;
    l.Free;
  end;
