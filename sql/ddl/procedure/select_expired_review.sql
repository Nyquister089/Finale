

Create procedure if not exists `tripdb`.`select_expired_review`()
begin
select distinct 
m.Targa, 
r.DataFine, 
r.Chilometraggio,
m.ValoreContaKm
from  mezzo as m
join revisione as r on m.Targa = r.MezzoRevisionato
where (m.ValoreContaKm > r.Chilometraggio) and m.Targa 
not in (select m1.Targa
		from mezzo as m1
		join revisione as r1 on m1.Targa=r1.MezzoRevisionato
		where DATE_ADD(r1.DataFine, INTERVAL 1 YEAR) >= CURDATE()
		and (m1.ValoreContaKm - r1.Chilometraggio) < '38000'); 
end