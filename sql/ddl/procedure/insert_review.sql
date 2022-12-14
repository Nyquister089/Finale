create procedure if not exists `tripdb`.`insert_review`(
in mzr varchar(45),
in mch varchar(45),
in dnz date, 
in dfn date,
in clm int, 
in cnt varchar(1000),
in tip varchar(45), 
in mtv varchar(1000)
)
BEGIN
insert into revisione (
   MezzoRevisionato,
   AddettoAllaRevisione,
   DataInizio,
   DataFine,
   Chilometraggio,
   ControlliEffettuati,
   TipologiaRevisione,
   Motivazione 
  )
values(
	mzr,
  mch,
	dnz, 
	dfn,
	clm, 
	cnt,
	tip, 
	mtv
); 
END