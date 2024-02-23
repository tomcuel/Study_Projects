function[max]=temperature_max(T0, Nbpt)
    max=0;
    for i=1:Nbpt
        if T0(i) >= max
            max=T0(i);
        end 
    end
    
    
    
end 


